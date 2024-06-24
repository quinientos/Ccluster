/* ************************************************************************** */
/*  Copyright (C) 2020 Remi Imbach                                            */
/*                                                                            */
/*  This file is part of Ccluster.                                            */
/*                                                                            */
/*  Ccluster is free software: you can redistribute it and/or modify it under */
/*  the terms of the GNU Lesser General Public License (LGPL) as published    */
/*  by the Free Software Foundation; either version 2.1 of the License, or    */
/*  (at your option) any later version.  See <http://www.gnu.org/licenses/>.  */
/* ************************************************************************** */

#ifndef CAUCHYTESTS_H
#define CAUCHYTESTS_H


#include "base/base.h"
#include "numbers/realRat.h"
#include "numbers/realApp.h"
#include "numbers/app_rat.h"
#include "caches/cacheApp.h"
#include "caches/cacheCauchy.h"
#include "metadatas/metadatas.h"

#include "geometry/compDsk.h"

#include "tstar/pelletTest.h"

#include "flint/acb_poly.h"

#include <flint/acb_dft.h>

#ifdef __cplusplus
extern "C" {
#endif
    
#define CAUCHYTEST_INCOUNTIN 1
#define CAUCHYTEST_INEXCLUSI 0  
    
typedef struct {
    int nbOfSol;   /* the number of solutions: -1: can not decide, >=0 otherwise */
    slong appPrec; /* the arithmetic precision that has been used to decide      */
} cauchyTest_res;    

void cauchyTest_getEvaluationPoints( const compRat_t center,
                                     const realRat_t radius,
                                     const realRat_t radius2,
                                     slong vangle,
                                     slong vindex,
                                     cacheCauchy_t cacheCau,
                                     slong prec );

void cauchyTest_evaluateAtPoints( cacheCauchy_t cacheCau,
                                  slong prec,
                                  int inCounting,
                                  metadatas_t meta, int depth);

/* returns -1: should increase precision
 *         -2: disk is has not expected isolation ratio; should stop
 *          1: OK! */
int cauchyTest_computeFdivs_fromVals(cacheCauchy_t cacheCau,
                                     slong prec,
                                     int inCounting,
                                     metadatas_t meta);

/* returns -1: should increase precision
 *         -2: disk is has not expected isolation ratio; should stop
 *          1: OK! */
int cauchyTest_computeS0Approx_fromVals(compApp_t ps,
                                        const realRat_t radius,
                                        cacheCauchy_t cacheCau,
                                        slong prec,
                                        int inCounting,
                                        metadatas_t meta);

/* computes approximation sh of h-th powersum */
void cauchyTest_computeShApprox_fromVals(compApp_t sh,
                                         slong h,
                                         const realRat_t radius,
                                         cacheCauchy_t cacheCau,
                                         slong prec,
                                         int inCounting,
                                         metadatas_t meta);

/* returns -1: should increase precision
 *         -2: disk is has not expected isolation ratio; should stop
 *          1: OK! */
int cauchyTest_computeSsApprox_fromVals(compApp_ptr ps,
                                        const realRat_t radius,
                                        cacheCauchy_t cacheCau,
                                        slong prec,
                                        int inCounting,
                                        metadatas_t meta);

cauchyTest_res cauchyTest_computeS0Approx(compApp_t ps,
                                          const compRat_t center,
                                          const realRat_t radius,
                                          const realRat_t radius2,
                                          slong vangle,           
                                          slong vindex,  
                                          int *alreadyEvaluated,
                                          cacheCauchy_t cacheCau,
                                          slong prec,
                                          int inCounting,
                                          metadatas_t meta, int depth );

cauchyTest_res cauchyTest_computeSsApprox(compApp_ptr ps,
                                          const compRat_t center,
                                          const realRat_t radius,
                                          const realRat_t radius2,
                                          slong vangle,           
                                          slong vindex,
                                          cacheCauchy_t cacheCau,
                                          slong prec,
                                          int inCounting,
                                          metadatas_t meta, int depth );

cauchyTest_res cauchyTest_probabilistic_exclusion_test( const compRat_t center,
                                                       const realRat_t radius,
                                                       const realRat_t radius2,
                                                       slong vangle,           
                                                       slong vindex,           
                                                       cacheCauchy_t cacheCau,
                                                       slong prec,
                                                       metadatas_t meta, int depth);

cauchyTest_res cauchyTest_probabilistic_counting( const compDsk_t Delta,           
                                                  cacheCauchy_t cacheCau,
                                                  slong prec,
                                                  metadatas_t meta, int depth);

/* this version works for any iso ratio, not necessarily the one
 * defined in CacheCau 
 * the disk is not necessarily isoRatio-isolated
 * can fail, otherwise
 * returns the number of roots in Delta */
cauchyTest_res cauchyTest_probabilistic_counting_withIsoRatio( const realRat_t isoRatio,
                                                               const compDsk_t Delta,
                                                               cacheCauchy_t cacheCau,
                                                               slong prec,
                                                               metadatas_t meta, int depth);

/* rootFreeAnnulus Counter */
/* implemented in cauchy_rootFreeAnnulus.c */
void cauchyTest_fmatheta( realRat_t res, const realRat_t a, const realRat_t theta );
void cauchyTest_fpatheta( realRat_t res, const realRat_t a, const realRat_t theta );
    
// cauchyTest_res cauchyTest_rootFreeAnnulus_counting( const compDsk_t Delta, 
//                                                   const realRat_t a,
//                                                   cacheCauchy_t cacheCau,
//                                                   slong prec,
//                                                   metadatas_t meta, int depth);

/* this version verifies that there are nbOfRoots roots in Delta */
cauchyTest_res cauchyTest_rootFreeAnnulus_verification( const compDsk_t Delta,
                                                      slong nbOfRoots,
                                                      const realRat_t a,
                                                      cacheCauchy_t cacheCau,
                                                      slong prec,
                                                      metadatas_t meta, int depth);

/* certification that A(center, radInf, radSup) contains no root: */
/* if  0 then A(center, radInf, radSup) contains no root */
/* if -1 then A(center, (radSup+radInf)/2 - (5/4)*isoRatio*(radSup-radInf)/2,  */
/*                      (radSup+radInf)/2 + (5/4)*isoRatio*(radSup-radInf)/2 ) */
/*             contains a root */
cauchyTest_res cauchyTest_rootFreeAnnulus( const compRat_t center,
                                           const realRat_t radInf,  
                                           const realRat_t radSup,
                                           cacheCauchy_t cacheCau,
                                           slong prec,
                                           metadatas_t meta, int depth);

cauchyTest_res cauchyTest_deterministic_counting_combinatorial( const compRat_t center,
                                                                     realRat_t radius,
                                                                     slong nbOfRoots,
                                                                     cacheCauchy_t cacheCau,
                                                                     slong prec,
                                                                     metadatas_t meta, int depth);

slong cauchyTest_getNbEvals_counting_combinatorial_with_rinfrsup(  const compRat_t c,
                                                                   const realRat_t rinf,
                                                                   const realRat_t rsup,
                                                                   slong m,
                                                                   cacheCauchy_t cacheCau);

slong cauchyTest_getNbEvals_counting_combinatorial_with_isoRatio( const compRat_t c,
                                                                  const realRat_t r,
                                                                  const realRat_t theta,
                                                                  slong m,
                                                                  cacheCauchy_t cacheCau);

cauchyTest_res cauchyTest_deterministic_counting_combinatorial_with_rinfrsup( const compRat_t c,
                                                                              const realRat_t rinf,
                                                                              const realRat_t rsup,
                                                                              slong m,
                                                                              cacheCauchy_t cacheCau,
                                                                              slong prec,
                                                                              metadatas_t meta, int depth);

cauchyTest_res cauchyTest_deterministic_counting_combinatorial_with_isoRatio( const compRat_t c,
                                                                              const realRat_t r,
                                                                              const realRat_t theta,
                                                                              slong m,
                                                                              cacheCauchy_t cacheCau,
                                                                              slong prec,
                                                                              metadatas_t meta, int depth);

void cauchyTest_computePointPointShifted( compApp_t point, compApp_t pointShifted, 
                                          const compApp_t center, slong q, slong i, const realRat_t radius,
                                          slong prec );
// void cauchyTest_eval ( compApp_ptr fvals, compApp_ptr fdervals, compApp_t points, slong nbPoints, cacheCauchy_t cacheCau, slong prec );
void cauchyTest_computeBounds ( realApp_t ubound, realApp_t lbound, 
                                const realRat_t theta, const realRat_t r, slong d, slong prec );
int  cauchyTest_compute_fdiv_checkPrecAndBounds( compApp_t fdiv, 
                                                 const compApp_t fval, 
                                                 const compApp_t fderval,
                                                 const realApp_t lbound,
                                                 const realApp_t ubound,
                                                 slong prec );

// int cauchyTest_shift_and_DLGs( compApp_poly_t dest, const compRat_t c, const realRat_t r, const realRat_t theta, cacheApp_t cache, 
//                                cacheCauchy_t cacheCau, slong prec, metadatas_t meta );

int cauchyTest_shift( compApp_poly_t dest, const compRat_t c, const realRat_t r, const realRat_t theta,
                               cacheCauchy_t cacheCau, slong prec, metadatas_t meta );

cauchyTest_res cauchyTest_Pellet_counting( const compRat_t c, const realRat_t r, const realRat_t theta, slong m,
                                                                              cacheCauchy_t cacheCau,
                                                                              slong prec,
                                                                              metadatas_t meta, int depth);

// cauchyTest_res cauchyTest_schroeders_counting( const compRat_t c, const realRat_t r, const realRat_t theta, slong m,
//                                                                               cacheCauchy_t cacheCau,
//                                                                               slong prec,
//                                                                               metadatas_t meta, int depth);

/* this version works for any iso ratio, not necessarily the one
 * defined in CacheCau 
 * the disk has to be isolated as isoRatio
 * returns the number of roots in Delta */
slong cauchyTest_computeS0compDsk( const realRat_t isoRatio,
                                   const compDsk_t Delta,
                                   cacheCauchy_t cacheCau,
                                   metadatas_t meta, int depth);

/* this version works for any iso ratio, not necessarily the one
 * defined in CacheCau 
 * the disk IS NOT NECESSARILY isoRatio-isolated;
 * can fail */
cauchyTest_res cauchyTest_computeS0compDsk_probabilistic( const realRat_t isoRatio,
                                                          const compDsk_t Delta,
                                                          cacheCauchy_t cacheCau,
                                                          metadatas_t meta, int depth);

/* Assume Delta is theta-isolated and contains nbOfRoots roots */
/* Computes a disk res with radius less than eps */
/* containing s1(p, Delta) */
/* if it returns res.nbOfSol = -2 then Delta is not theta-isolated */
slong cauchyTest_computeS1compDsk( compDsk_t res,
                                            const realRat_t theta,
                                            const compDsk_t Delta,
                                            slong nbOfRoots,
                                            cacheCauchy_t cacheCau,
                                            const realRat_t eps,
                                            metadatas_t meta, int depth);

/* Assume Delta is isoRatio-isolated and contains m roots     */
/* Let h be a non-negative integer                            */
/* Assume SS is initialized to contain at least h + 1 numbers */
/* Computes h + 1 first power sums with error less than eps   */
cauchyTest_res cauchyTest_computeSScompDsk( compApp_ptr SS,
                                   const realRat_t isoRatio,
                                   const compDsk_t Delta,
                                   slong m,
                                   slong h,
                                   cacheCauchy_t cacheCau,
                                   const realRat_t eps,
                                   slong prec,
                                   metadatas_t meta, int depth);

/* Assume Delta is isoRatio-isolated and contains m roots     */
/* Let N be a non-negative integer                            */
/* Assume SS is initialized to contain at least m + 1 numbers */
/* Computes power sums sN, s2N, ..., smN with error less than eps   */
cauchyTest_res cauchyTest_computeSgNcompDsk( compApp_ptr SgN,
                                             const realRat_t isoRatio,
                                             const compDsk_t Delta,
                                             slong m,
                                             ulong N,
                                             slong h,
                                             cacheCauchy_t cacheCau,
                                             const realRat_t eps,
                                             slong prec,
                                             metadatas_t meta, int depth);

/* DEPRECATED */

// cauchyTest_res cauchyTest_deterministic_exclusion_test( const compRat_t center,
//                                                        const realRat_t radius,
//                                                        const realRat_t radius2,
//                                                        slong vangle,           
//                                                        slong vindex,    
//                                                        cacheCauchy_t cacheCau,
//                                                        slong prec,
//                                                        int inCounting,
//                                                        metadatas_t meta, int depth);
// 
// cauchyTest_res cauchyTest_deterministic_exclusion_testNEW( const compRat_t center,
//                                                        const realRat_t radius,
//                                                        const realRat_t radius2,
//                                                        slong vangle,           
//                                                        slong vindex,    
//                                                        cacheCauchy_t cacheCau,
//                                                        slong prec,
//                                                        int inCounting,
//                                                        metadatas_t meta, int depth);

#ifdef __cplusplus
}
#endif

#endif
