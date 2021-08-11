#!/bin/bash

format_time()
{
    TIME1=$1
    TIME2=$1
    TIME1=`echo $TIME1 | cut -f1 -d'.'`
    TIME2=`echo $TIME2 | cut -f2 -d'.'`
    STIME1=${#TIME1}
    STIME1=$(( 3 - $STIME1 ))
    STIME2=$(( 3 < $STIME1 ? 3 : $STIME1 ))
    STIME2=$(( 0 > $STIME2 ? 0 : $STIME2 ))
    if [ $STIME2 -eq 0 ]; then
        echo $TIME1
    else
        TIME2=`echo $TIME2 | cut -c-$( echo $STIME2)`
        echo $TIME1"."$TIME2
    fi
}

init_rep()
{
    REP=$1
    if [ -d "$REP" ]; then
        if [ $PURGE -eq 1 ]; then
            rm -rf $REP
            mkdir $REP
        fi
    else
        mkdir $REP
    fi
}

gen_with_deg(){

    NAME=$1
    POLNAME=$2
    DEG=$3
    NAME_IN=$NAME".ccl"
    NAME_IN2=$NAME".mpl"
    NAME_IN3=$NAME".dsc"
    
    if [ ! -e $NAME_IN ]; then
            $ECHO "Generating file for $POLNAME degree $DEG, pol in " $NAME_IN
            if [ $VERBOSE -eq 1 ]; then
                $GENPOLFILE_CALL $POLNAME $DEG $NAME_IN -f 1
            else
                $GENPOLFILE_CALL $POLNAME $DEG $NAME_IN -f 1 >/dev/null
            fi
    fi
    
    if [ ! -e $NAME_IN2 ]; then
            $ECHO  "Generating file for $POLNAME degree $DEG, pol in " $NAME_IN2
            if [ $VERBOSE -eq 1 ]; then
                $GENPOLFILE_CALL $POLNAME $DEG $NAME_IN2 -f 2
            else
                $GENPOLFILE_CALL $POLNAME $DEG $NAME_IN2 -f 2 >/dev/null
            fi
    fi
    
    if [ ! -e $NAME_IN3 ]; then
            $ECHO  "Generating file for $POLNAME degree $DEG, pol in " $NAME_IN3
            if [ $VERBOSE -eq 1 ]; then
                $GENPOLFILE_CALL $POLNAME $DEG $NAME_IN3 -f 3
            else
                $GENPOLFILE_CALL $POLNAME $DEG $NAME_IN3 -f 3 >/dev/null
            fi
    fi
    
}

gen_with_deg_bs(){

    NAME=$1
    POLNAME=$2
    DEG=$3
    BIT=$4
    NAME_IN=$NAME".ccl"
    NAME_IN2=$NAME".mpl"
    NAME_IN3=$NAME".dsc"
    
    if [ ! -e $NAME_IN ]; then
            $ECHO "Generating file for $POLNAME degree $DEG, bitsize $BIT, pol in " $NAME_IN
            if [ $VERBOSE -eq 1 ]; then
                $GENPOLFILE_CALL $POLNAME $DEG $NAME_IN -f 1 -b $BIT
            else
                $GENPOLFILE_CALL $POLNAME $DEG $NAME_IN -f 1 -b $BIT >/dev/null
            fi
    fi
    
    if [ ! -e $NAME_IN2 ]; then
            $ECHO  "Generating file for $POLNAME degree $DEG, bitsize $BIT, pol in " $NAME_IN2
            if [ $VERBOSE -eq 1 ]; then
                $GENPOLFILE_CALL $POLNAME $DEG $NAME_IN2 -f 2 -b $BIT 
            else
                $GENPOLFILE_CALL $POLNAME $DEG $NAME_IN2 -f 2 -b $BIT >/dev/null
            fi
    fi
    
    if [ ! -e $NAME_IN3 ]; then
            $ECHO  "Generating file for $POLNAME degree $DEG, bitsize $BIT, pol in " $NAME_IN3
            if [ $VERBOSE -eq 1 ]; then
                $GENPOLFILE_CALL $POLNAME $DEG $NAME_IN3 -f 3 -b $BIT 
            else
                $GENPOLFILE_CALL $POLNAME $DEG $NAME_IN3 -f 3 -b $BIT >/dev/null
            fi
    fi
    
}

gen_with_deg_rw_ns(){

    NAME=$1
    POLNAME=$2
    DEG=$3
    RW=$4
    NS=$5
    NAME_IN=$NAME".ccl"
    NAME_IN2=$NAME".mpl"
    NAME_IN3=$NAME".dsc"
    
    if [ ! -e $NAME_IN ]; then
            $ECHO "Generating file for $POLNAME iterations $DEG, a=$RW, c=$NS, bitsize $BIT, pol in " $NAME_IN
            if [ $VERBOSE -eq 1 ]; then
                $GENPOLFILE_CALL $POLNAME $DEG $NAME_IN -f 1 -c $NS -a $RW
            else
                $GENPOLFILE_CALL $POLNAME $DEG $NAME_IN -f 1 -c $NS -a $RW >/dev/null
            fi
    fi
    
    if [ ! -e $NAME_IN2 ]; then
            $ECHO  "Generating file for $POLNAME degree $DEG, a=$RW, c=$NS, pol in " $NAME_IN2
            if [ $VERBOSE -eq 1 ]; then
                $GENPOLFILE_CALL $POLNAME $DEG $NAME_IN2 -f 2 -c $NS -a $RW 
            else
                $GENPOLFILE_CALL $POLNAME $DEG $NAME_IN2 -f 2 -c $NS -a $RW >/dev/null
            fi
    fi
    
    if [ ! -e $NAME_IN3 ]; then
            $ECHO  "Generating file for $POLNAME degree $DEG, a=$RW, c=$NS, pol in " $NAME_IN3
            if [ $VERBOSE -eq 1 ]; then
                $GENPOLFILE_CALL $POLNAME $DEG $NAME_IN3 -f 3 -c $NS -a $RW 
            else
                $GENPOLFILE_CALL $POLNAME $DEG $NAME_IN3 -f 3 -c $NS -a $RW >/dev/null
            fi
    fi
    
}

run_ccluster_local_global()
{
    NAME=$1
    POLNAME=$2
    DEG=$3
    NAME_IN=$NAME".ccl"
    NAME_OUTLOCAL=$NAME".out_ccl_local"
    NAME_OUTGLOBAL=$NAME".out_ccl_global"
    
    if [ $PURGECCLLOCAL -eq 1 ]; then
        rm -f $NAME_OUTLOCAL
    fi
    
    if [ $PURGECCLGLOBAL -eq 1 ]; then
        rm -f $NAME_OUTGLOBAL
    fi
    
    if [ ! -e $NAME_OUTLOCAL ]; then
            $ECHO  "Clustering complex roots for $POLNAME degree $DEG, RoI: $BLOCAL, default, output in " $NAME_OUTLOCAL
            CALL="$CCLUSTER_CALL $NAME_IN -d $BLOCAL -e $EPSILONCCL -v 2 -m $MFLAG"
            $CALL > $NAME_OUTLOCAL
    fi
  
    if [ ! -e $NAME_OUTGLOBAL ]; then
            $ECHO  "Clustering complex roots for $POLNAME degree $DEG, global, root radii, output in " $NAME_OUTGLOBAL
            CALL="$CCLUSTER_CALL $NAME_IN -e $EPSILONCCL -v 2 -m $MFLAG"
            $CALL > $NAME_OUTGLOBAL
    fi
    
}

run_mpsolve()
{
    NAME=$1
    POLNAME=$2
    DEG=$3
    NAME_IN=$NAME".mpl"
    NAME_OUT=$NAME".out_mpl"
    
    if [ $PURGEMPSOLVE -eq 1 ]; then
        rm -f $NAME_OUT
    fi
    
    if [ ! -e $NAME_OUT ]; then
            $ECHO "Approximating roots ($EPSILONMPS correct digits after the .)  in C with MPSOLVE SECSOLVE........."
            (/usr/bin/time -f "real\t%e" $MPSOLVE_CALL_S $NAME_IN > $NAME_OUT) &>> $NAME_OUT
    fi
    
}

HEAD_TABLE="\begin{tabular}{l||c|c|c||c|c|c||c|}"
FIRST_LINE="     & \multicolumn{3}{|c||}{\texttt{Ccluster} local (\$[-1,1]^2\$)}"
FIRST_LINE=$FIRST_LINE"& \multicolumn{3}{|c||}{\texttt{Ccluster} global}"
FIRST_LINE=$FIRST_LINE"& \texttt{secsolve} \\\\\\hline"
SECOND_LINE="d& (\#Sols:\#Clus) & (depth:size) & \$\tau_\ell\$ (s)"
SECOND_LINE=$SECOND_LINE"& (\#Sols:\#Clus) & (depth:size) & \$\tau_g\$ (s)"
SECOND_LINE=$SECOND_LINE"& \$\tau_s\$ (s)   \\\\\\hline\hline"
TAIL_TAB="\end{tabular}"

stats_pol_ccluster_l_g_mpsolve()
{
    NAME=$1
    NAME_OUTLOCAL=$NAME".out_ccl_local"
    NAME_OUTGLOBAL=$NAME".out_ccl_global"
    NAME_OUTMPS=$NAME".out_mpl"
    
    DEGREE=$(grep "degree:"                  $NAME_OUTLOCAL| cut -f3 -d':'| cut -f1 -d'b' | cut -f1 -d'|' | tr -d ' ')
    BITSIZE=$(grep "bitsize:"                $NAME_OUTLOCAL| cut -f4 -d':'| cut -f1 -d's' | cut -f1 -d'|' | tr -d ' ')
    TCCLUSTER_L=$(grep "time:" $NAME_OUTLOCAL| cut -f2 -d':'| cut -f1 -d's' | cut -f1 -d'|' | tr -d ' ')
    TDCCLUSTER_L=$(grep "tree depth:" $NAME_OUTLOCAL| cut -f2 -d':' | cut -f1 -d'|' | tr -d ' ')
    TSCCLUSTER_L=$(grep "tree size:" $NAME_OUTLOCAL| cut -f2 -d':' | cut -f1 -d'|' | tr -d ' ')
    NBCLUSTERS_L=$(grep "number of clusters:" $NAME_OUTLOCAL| cut -f2 -d':' | cut -f1 -d'|' | tr -d ' ')
    NBSOLUTION_L=$(grep "number of solutions:" $NAME_OUTLOCAL| cut -f2 -d':' | cut -f1 -d'|' | tr -d ' ')
    
    TCCLUSTER_G=$(grep "time:" $NAME_OUTGLOBAL| cut -f2 -d':'| cut -f1 -d's' | cut -f1 -d'|' | tr -d ' ')
    TDCCLUSTER_G=$(grep "tree depth:" $NAME_OUTGLOBAL| cut -f2 -d':' | cut -f1 -d'|' | tr -d ' ')
    TSCCLUSTER_G=$(grep "tree size:" $NAME_OUTGLOBAL| cut -f2 -d':' | cut -f1 -d'|' | tr -d ' ')
    NBCLUSTERS_G=$(grep "number of clusters:" $NAME_OUTGLOBAL| cut -f2 -d':' | cut -f1 -d'|' | tr -d ' ')
    NBSOLUTION_G=$(grep "number of solutions:" $NAME_OUTGLOBAL| cut -f2 -d':' | cut -f1 -d'|' | tr -d ' ')
    
    TMPSOLVE_S=$(grep "real" $NAME_OUTMPS| cut -f2 -d'l' | tr -d ' ')
    
    LINE_TAB=$DEGREE"&"$BITSIZE"&("$NBSOLUTION_L":"$NBCLUSTERS_L")&("$TDCCLUSTER_L":"$TSCCLUSTER_L")&`format_time $TCCLUSTER_L`"
    LINE_TAB=$LINE_TAB"&("$NBSOLUTION_G":"$NBCLUSTERS_G")&("$TDCCLUSTER_G":"$TSCCLUSTER_G")&`format_time $TCCLUSTER_G`"
    LINE_TAB=$LINE_TAB"&"$TMPSOLVE"&"$TMPSOLVE_S
    LINE_TAB=$LINE_TAB"\\\\\\hline"
    
    echo $LINE_TAB >> $TEMPTABFILE
}
