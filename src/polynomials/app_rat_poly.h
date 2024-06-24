/* ************************************************************************** */
/*  Copyright (C) 2018 Remi Imbach                                            */
/*                                                                            */
/*  This file is part of Ccluster.                                            */
/*                                                                            */
/*  Ccluster is free software: you can redistribute it and/or modify it under */
/*  the terms of the GNU Lesser General Public License (LGPL) as published    */
/*  by the Free Software Foundation; either version 2.1 of the License, or    */
/*  (at your option) any later version.  See <http://www.gnu.org/licenses/>.  */
/* ************************************************************************** */

#ifndef APPRAT_POLY_H
#define APPRAT_POLY_H

#ifdef POLYNOMIALS_INLINE_C
#define POLYNOMIALS_INLINE
#else
#define POLYNOMIALS_INLINE static __inline__
#endif

#include "flint/mag.h"
#include "numbers/app_rat.h"
#include "polynomials/realRat_poly.h"
#include "polynomials/compRat_poly.h"
#include "polynomials/realApp_poly.h"
#include "polynomials/compApp_poly.h"

#ifdef __cplusplus
extern "C" {
#endif

/* converting realRat_poly to realApp_poly  */
POLYNOMIALS_INLINE void realApp_poly_set_realRat_poly(realApp_poly_t poly, const realRat_poly_t re, slong prec){
    arb_poly_set_fmpq_poly(poly, re, prec);
}

/* converting realRat_poly to compApp_poly  */
POLYNOMIALS_INLINE void compApp_poly_set_realRat_poly(compApp_poly_t poly, const realRat_poly_t re, slong prec) {
    compApp_poly_set_fmpq_poly(poly, re, prec);
}

/* converting compRat_poly to compApp_poly  */
POLYNOMIALS_INLINE void compApp_poly_set_compRat_poly(compApp_poly_t poly, const compRat_poly_t pRat, slong prec) {
    compApp_poly_set2_fmpq_poly(poly, compRat_poly_realref(pRat), compRat_poly_imagref(pRat), prec);
}

/* root bound */
void compApp_poly_root_bound_fujiwara(realRat_t bound, compApp_poly_t poly);

/* scaling in place */
/* requires: r is canonical */ 
void realApp_poly_scale_realRat_in_place( realApp_ptr fptr, const realRat_t r, slong len, slong prec);

void compApp_poly_scale_realRat_in_place( compApp_ptr fptr, const realRat_t r, slong len, slong prec );

void compApp_poly_scale_realRat_in_place_monic( compApp_ptr fptr, const realRat_t r, slong len, slong prec );

void realApp_poly_taylorShift_in_place( realApp_poly_t f, 
                                        const realRat_t center, 
                                        const realRat_t radius, 
                                        slong prec );

void compApp_poly_taylorShift_in_place( compApp_poly_t f, 
                                        const compRat_t center, 
                                        const realRat_t radius, 
                                        slong prec );


void compApp_poly_taylorShift_in_place_noscale( compApp_poly_t f, 
                                        const compRat_t center, 
                                        slong prec );

// void compApp_poly_taylorShift_in_place_noscale_compApp( compApp_poly_t f, 
//                                                         const compApp_t center, 
//                                                         slong prec );

void realApp_poly_taylorShift_in_place_noscale( realApp_poly_t f, 
                                        const realRat_t center, 
                                        slong prec );

void compApp_poly_taylorShift_interval_in_place( compApp_poly_t f, const compRat_t center, const realRat_t radius, slong prec );
void realApp_poly_taylorShift_interval_in_place( realApp_poly_t f, const realRat_t center, const realRat_t radius, slong prec );

void realApp_poly_taylorShift_in_place_slong( realApp_poly_t f, 
                                              slong centeRe, 
                                              slong prec );

void compApp_poly_taylorShift_in_place_slong( compApp_poly_t f, 
                                              slong centerRe, 
                                              slong centerIm,
                                              slong prec );


void realApp_poly_taylorShift( realApp_poly_t res, 
                               const realApp_poly_t f, 
                               const realRat_t center, 
                               const realRat_t radius, 
                               slong prec );

void compApp_poly_taylorShift( compApp_poly_t res, 
                               const compApp_poly_t f, 
                               const compRat_t center, 
                               const realRat_t radius, 
                               slong prec );

/* evaluate at order 1 on an interval geven by center + width */
void realApp_poly_evaluate_order_one( realApp_t y, const realApp_poly_t f, const realApp_poly_t fder, const realRat_t c, const realRat_t w, slong prec);

/*void compApp_poly_taylorShift_in_place_new( compApp_poly_t f, const realRat_t creal, const realRat_t cimag, const realRat_t radius, slong prec );*/
void compApp_poly_taylor_shift_convolution_without_pre(compApp_poly_t dest, const compApp_poly_t p, 
                                                       realApp_t f, compApp_ptr t, 
                                                       const realRat_t creal, const realRat_t cimag, const realRat_t radius,
                                                       slong prec);

void compApp_poly_taylorShift_new( compApp_poly_t res, 
                               const compApp_poly_t f, 
                               const realRat_t creal, const realRat_t cimag, const realRat_t radius, 
                               slong prec );

void _compApp_poly_parallel_taylor_inplace( compApp_poly_t p, const compApp_t c, const realRat_t radius, slong prec, slong num_threads);
void compApp_poly_parallel_taylor_inplace( compApp_poly_t p, const realRat_t creal, const realRat_t cimag, const realRat_t radius, slong prec, slong num_threads);
void compApp_poly_parallel_taylor( compApp_poly_t dest, const compApp_poly_t p, const realRat_t creal, const realRat_t cimag, const realRat_t radius, slong prec, slong num_threads);

void compApp_poly_parallel_taylor_convol(compApp_poly_t dest, const compApp_poly_t p, const compApp_t c, const realRat_t radius, slong prec, slong num_threads);

#ifdef __cplusplus
}
#endif

#endif
