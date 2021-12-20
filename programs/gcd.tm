; 最大公约数求解可以通过辗转相减法解决
; 先检测是否是合法的输入串

#Q = {0,left,right,middle,correct,begin,tape1_larger_tape2,tape1_larger_tape2_back2,tape2_larger_tape1,tape2_larger_tape1_back2,end,end_back_begin,end_back,accept_clear,begin_copy,halt_accept,reject,reject2,reject3,reject4,reject5,reject6,reject7,reject8,reject9,reject10,reject11,reject12,halt_reject,reject_clear}

#S = {0,1}

#G = {0,1,_,i,l,e,g,a,p,n,u,t}

#q0 = 0

#B = _

#F = {halt_accept}

#N = 3

; the transition functions

0 1__ *1* rr* left


left 1__ *1* rr* left
left ___ *** *** reject_clear
left 0__ *** r** middle

middle 1__ **1 r*r right
middle 0__ *** *** reject_clear

right 1__ **1 r*r right
right ___ *** *** correct ;???
right 0__ *** *** reject_clear


correct *__ *** *ll begin

begin *11 *** *ll begin
begin *__ *** *** end_back
begin *_1 *** *rr tape1_larger_tape2
begin *1_ *** *rr tape2_larger_tape1

tape1_larger_tape2 *11 *1_ *rr tape1_larger_tape2
tape1_larger_tape2 *__ *** *** tape1_larger_tape2_back2

tape1_larger_tape2_back2 *__ *** **l tape1_larger_tape2_back2
tape1_larger_tape2_back2 *_1 *** **r correct

tape2_larger_tape1 *11 *_1 *rr tape2_larger_tape1
tape2_larger_tape1 *__ *** *** tape2_larger_tape1_back2

tape2_larger_tape1_back2 *__ *** *l* tape2_larger_tape1_back2
tape2_larger_tape1_back2 *1_ *** *r* correct




end_back *__ *** *rr end_back_begin
end_back_begin *** *** *rr end_back_begin
end_back_begin *__ *** *** end


end _** *** l** accept_clear

accept_clear *__ _** l** accept_clear
accept_clear ___ *** *ll begin_copy

begin_copy _11 1** lll begin_copy
begin_copy ___ *** *** halt_accept 

reject_clear *** *** r** reject_clear
reject_clear _** ___ lll reject

reject *** ___ lll reject
reject ___ i__ r** reject2
reject2 ___ l__ r** reject3
reject3 ___ l__ r** reject4
reject4 ___ e__ r** reject5
reject5 ___ g__ r** reject6
reject6 ___ a__ r** reject7
reject7 ___ l__ r** reject8
reject8 ___ i__ r** reject9
reject9 ___ n__ r** reject10
reject10 ___ p__ r** reject11
reject11 ___ u__ r** reject12
reject12 ___ t__ *** halt_reject