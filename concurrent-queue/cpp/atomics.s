	.section	__TEXT,__text,regular,pure_instructions
	.build_version macos, 14, 0	sdk_version 14, 2
	.globl	__Z8producerv                   ; -- Begin function _Z8producerv
	.p2align	2
__Z8producerv:                          ; @_Z8producerv
	.cfi_startproc
; %bb.0:
	mov	w8, #100
Lloh0:
	adrp	x9, _data@PAGE
	str	w8, [x9, _data@PAGEOFF]
	mov	w8, #1
Lloh1:
	adrp	x9, _ready@PAGE
	strb	w8, [x9, _ready@PAGEOFF]
	ret
	.loh AdrpAdrp	Lloh0, Lloh1
	.cfi_endproc
                                        ; -- End function
	.globl	__Z8consumerv                   ; -- Begin function _Z8consumerv
	.p2align	2
__Z8consumerv:                          ; @_Z8consumerv
	.cfi_startproc
; %bb.0:
	stp	x29, x30, [sp, #-16]!           ; 16-byte Folded Spill
	.cfi_def_cfa_offset 16
	mov	x29, sp
	.cfi_def_cfa w29, 16
	.cfi_offset w30, -8
	.cfi_offset w29, -16
	adrp	x8, _ready@PAGE
LBB1_1:                                 ; =>This Inner Loop Header: Depth=1
	ldrb	w9, [x8, _ready@PAGEOFF]
	tbz	w9, #0, LBB1_1
; %bb.2:
Lloh2:
	adrp	x8, _data@PAGE
Lloh3:
	ldr	w8, [x8, _data@PAGEOFF]
	cmp	w8, #100
	b.ne	LBB1_4
; %bb.3:
	ldp	x29, x30, [sp], #16             ; 16-byte Folded Reload
	ret
LBB1_4:
	bl	__Z8consumerv.cold.1
	.loh AdrpLdr	Lloh2, Lloh3
	.cfi_endproc
                                        ; -- End function
	.globl	_main                           ; -- Begin function main
	.p2align	2
_main:                                  ; @main
Lfunc_begin0:
	.cfi_startproc
	.cfi_personality 155, ___gxx_personality_v0
	.cfi_lsda 16, Lexception0
; %bb.0:
	sub	sp, sp, #48
	.cfi_def_cfa_offset 48
	stp	x20, x19, [sp, #16]             ; 16-byte Folded Spill
	stp	x29, x30, [sp, #32]             ; 16-byte Folded Spill
	add	x29, sp, #32
	.cfi_def_cfa w29, 16
	.cfi_offset w30, -8
	.cfi_offset w29, -16
	.cfi_offset w19, -24
	.cfi_offset w20, -32
Lloh4:
	adrp	x1, __Z8producerv@PAGE
Lloh5:
	add	x1, x1, __Z8producerv@PAGEOFF
	add	x0, sp, #8
	bl	__ZNSt3__16threadC2IRFvvEJEvEEOT_DpOT0_
Ltmp0:
Lloh6:
	adrp	x1, __Z8consumerv@PAGE
Lloh7:
	add	x1, x1, __Z8consumerv@PAGEOFF
	mov	x0, sp
	bl	__ZNSt3__16threadC2IRFvvEJEvEEOT_DpOT0_
Ltmp1:
; %bb.1:
Ltmp3:
	add	x0, sp, #8
	bl	__ZNSt3__16thread4joinEv
Ltmp4:
; %bb.2:
Ltmp5:
	mov	x0, sp
	bl	__ZNSt3__16thread4joinEv
Ltmp6:
; %bb.3:
	mov	x0, sp
	bl	__ZNSt3__16threadD1Ev
	add	x0, sp, #8
	bl	__ZNSt3__16threadD1Ev
	mov	w0, #0
	ldp	x29, x30, [sp, #32]             ; 16-byte Folded Reload
	ldp	x20, x19, [sp, #16]             ; 16-byte Folded Reload
	add	sp, sp, #48
	ret
LBB2_4:
Ltmp2:
	mov	x19, x0
	b	LBB2_6
LBB2_5:
Ltmp7:
	mov	x19, x0
	mov	x0, sp
	bl	__ZNSt3__16threadD1Ev
LBB2_6:
	add	x0, sp, #8
	bl	__ZNSt3__16threadD1Ev
	mov	x0, x19
	bl	__Unwind_Resume
	.loh AdrpAdd	Lloh6, Lloh7
	.loh AdrpAdd	Lloh4, Lloh5
Lfunc_end0:
	.cfi_endproc
	.section	__TEXT,__gcc_except_tab
	.p2align	2, 0x0
GCC_except_table2:
Lexception0:
	.byte	255                             ; @LPStart Encoding = omit
	.byte	255                             ; @TType Encoding = omit
	.byte	1                               ; Call site Encoding = uleb128
	.uleb128 Lcst_end0-Lcst_begin0
Lcst_begin0:
	.uleb128 Lfunc_begin0-Lfunc_begin0      ; >> Call Site 1 <<
	.uleb128 Ltmp0-Lfunc_begin0             ;   Call between Lfunc_begin0 and Ltmp0
	.byte	0                               ;     has no landing pad
	.byte	0                               ;   On action: cleanup
	.uleb128 Ltmp0-Lfunc_begin0             ; >> Call Site 2 <<
	.uleb128 Ltmp1-Ltmp0                    ;   Call between Ltmp0 and Ltmp1
	.uleb128 Ltmp2-Lfunc_begin0             ;     jumps to Ltmp2
	.byte	0                               ;   On action: cleanup
	.uleb128 Ltmp3-Lfunc_begin0             ; >> Call Site 3 <<
	.uleb128 Ltmp6-Ltmp3                    ;   Call between Ltmp3 and Ltmp6
	.uleb128 Ltmp7-Lfunc_begin0             ;     jumps to Ltmp7
	.byte	0                               ;   On action: cleanup
	.uleb128 Ltmp6-Lfunc_begin0             ; >> Call Site 4 <<
	.uleb128 Lfunc_end0-Ltmp6               ;   Call between Ltmp6 and Lfunc_end0
	.byte	0                               ;     has no landing pad
	.byte	0                               ;   On action: cleanup
Lcst_end0:
	.p2align	2, 0x0
                                        ; -- End function
	.section	__TEXT,__text,regular,pure_instructions
	.private_extern	__ZNSt3__16threadC2IRFvvEJEvEEOT_DpOT0_ ; -- Begin function _ZNSt3__16threadC2IRFvvEJEvEEOT_DpOT0_
	.globl	__ZNSt3__16threadC2IRFvvEJEvEEOT_DpOT0_
	.weak_def_can_be_hidden	__ZNSt3__16threadC2IRFvvEJEvEEOT_DpOT0_
	.p2align	2
__ZNSt3__16threadC2IRFvvEJEvEEOT_DpOT0_: ; @_ZNSt3__16threadC2IRFvvEJEvEEOT_DpOT0_
Lfunc_begin1:
	.cfi_startproc
	.cfi_personality 155, ___gxx_personality_v0
	.cfi_lsda 16, Lexception1
; %bb.0:
	sub	sp, sp, #64
	.cfi_def_cfa_offset 64
	stp	x22, x21, [sp, #16]             ; 16-byte Folded Spill
	stp	x20, x19, [sp, #32]             ; 16-byte Folded Spill
	stp	x29, x30, [sp, #48]             ; 16-byte Folded Spill
	add	x29, sp, #48
	.cfi_def_cfa w29, 16
	.cfi_offset w30, -8
	.cfi_offset w29, -16
	.cfi_offset w19, -24
	.cfi_offset w20, -32
	.cfi_offset w21, -40
	.cfi_offset w22, -48
	mov	x20, x1
	mov	x19, x0
	mov	w0, #8
	bl	__Znwm
	mov	x21, x0
Ltmp8:
	bl	__ZNSt3__115__thread_structC1Ev
Ltmp9:
; %bb.1:
	str	x21, [sp, #8]
Ltmp11:
	mov	w0, #16
	bl	__Znwm
Ltmp12:
; %bb.2:
	mov	x3, x0
	stp	x0, xzr, [sp]
	stp	x21, x20, [x0]
Ltmp14:
Lloh8:
	adrp	x2, __ZNSt3__114__thread_proxyB7v160006INS_5tupleIJNS_10unique_ptrINS_15__thread_structENS_14default_deleteIS3_EEEEPFvvEEEEEEPvSA_@PAGE
Lloh9:
	add	x2, x2, __ZNSt3__114__thread_proxyB7v160006INS_5tupleIJNS_10unique_ptrINS_15__thread_structENS_14default_deleteIS3_EEEEPFvvEEEEEEPvSA_@PAGEOFF
	mov	x0, x19
	mov	x1, #0
	bl	_pthread_create
Ltmp15:
; %bb.3:
	cbnz	w0, LBB3_5
; %bb.4:
	mov	x0, x19
	ldp	x29, x30, [sp, #48]             ; 16-byte Folded Reload
	ldp	x20, x19, [sp, #32]             ; 16-byte Folded Reload
	ldp	x22, x21, [sp, #16]             ; 16-byte Folded Reload
	add	sp, sp, #64
	ret
LBB3_5:
Ltmp16:
Lloh10:
	adrp	x1, l_.str.2@PAGE
Lloh11:
	add	x1, x1, l_.str.2@PAGEOFF
	bl	__ZNSt3__120__throw_system_errorEiPKc
Ltmp17:
; %bb.6:
	brk	#0x1
LBB3_7:
Ltmp13:
	mov	x19, x0
	b	LBB3_10
LBB3_8:
Ltmp10:
	mov	x19, x0
	mov	x0, x21
	bl	__ZdlPv
	mov	x0, x19
	bl	__Unwind_Resume
LBB3_9:
Ltmp18:
	mov	x19, x0
	mov	x0, sp
	bl	__ZNSt3__110unique_ptrINS_5tupleIJNS0_INS_15__thread_structENS_14default_deleteIS2_EEEEPFvvEEEENS3_IS8_EEED1B7v160006Ev
LBB3_10:
	add	x0, sp, #8
	bl	__ZNSt3__110unique_ptrINS_15__thread_structENS_14default_deleteIS1_EEED1B7v160006Ev
	mov	x0, x19
	bl	__Unwind_Resume
	.loh AdrpAdd	Lloh8, Lloh9
	.loh AdrpAdd	Lloh10, Lloh11
Lfunc_end1:
	.cfi_endproc
	.section	__TEXT,__gcc_except_tab
	.p2align	2, 0x0
GCC_except_table3:
Lexception1:
	.byte	255                             ; @LPStart Encoding = omit
	.byte	255                             ; @TType Encoding = omit
	.byte	1                               ; Call site Encoding = uleb128
	.uleb128 Lcst_end1-Lcst_begin1
Lcst_begin1:
	.uleb128 Lfunc_begin1-Lfunc_begin1      ; >> Call Site 1 <<
	.uleb128 Ltmp8-Lfunc_begin1             ;   Call between Lfunc_begin1 and Ltmp8
	.byte	0                               ;     has no landing pad
	.byte	0                               ;   On action: cleanup
	.uleb128 Ltmp8-Lfunc_begin1             ; >> Call Site 2 <<
	.uleb128 Ltmp9-Ltmp8                    ;   Call between Ltmp8 and Ltmp9
	.uleb128 Ltmp10-Lfunc_begin1            ;     jumps to Ltmp10
	.byte	0                               ;   On action: cleanup
	.uleb128 Ltmp11-Lfunc_begin1            ; >> Call Site 3 <<
	.uleb128 Ltmp12-Ltmp11                  ;   Call between Ltmp11 and Ltmp12
	.uleb128 Ltmp13-Lfunc_begin1            ;     jumps to Ltmp13
	.byte	0                               ;   On action: cleanup
	.uleb128 Ltmp14-Lfunc_begin1            ; >> Call Site 4 <<
	.uleb128 Ltmp17-Ltmp14                  ;   Call between Ltmp14 and Ltmp17
	.uleb128 Ltmp18-Lfunc_begin1            ;     jumps to Ltmp18
	.byte	0                               ;   On action: cleanup
	.uleb128 Ltmp17-Lfunc_begin1            ; >> Call Site 5 <<
	.uleb128 Lfunc_end1-Ltmp17              ;   Call between Ltmp17 and Lfunc_end1
	.byte	0                               ;     has no landing pad
	.byte	0                               ;   On action: cleanup
Lcst_end1:
	.p2align	2, 0x0
                                        ; -- End function
	.section	__TEXT,__text,regular,pure_instructions
	.private_extern	__ZNSt3__114__thread_proxyB7v160006INS_5tupleIJNS_10unique_ptrINS_15__thread_structENS_14default_deleteIS3_EEEEPFvvEEEEEEPvSA_ ; -- Begin function _ZNSt3__114__thread_proxyB7v160006INS_5tupleIJNS_10unique_ptrINS_15__thread_structENS_14default_deleteIS3_EEEEPFvvEEEEEEPvSA_
	.globl	__ZNSt3__114__thread_proxyB7v160006INS_5tupleIJNS_10unique_ptrINS_15__thread_structENS_14default_deleteIS3_EEEEPFvvEEEEEEPvSA_
	.weak_definition	__ZNSt3__114__thread_proxyB7v160006INS_5tupleIJNS_10unique_ptrINS_15__thread_structENS_14default_deleteIS3_EEEEPFvvEEEEEEPvSA_
	.p2align	2
__ZNSt3__114__thread_proxyB7v160006INS_5tupleIJNS_10unique_ptrINS_15__thread_structENS_14default_deleteIS3_EEEEPFvvEEEEEEPvSA_: ; @_ZNSt3__114__thread_proxyB7v160006INS_5tupleIJNS_10unique_ptrINS_15__thread_structENS_14default_deleteIS3_EEEEPFvvEEEEEEPvSA_
Lfunc_begin2:
	.cfi_startproc
	.cfi_personality 155, ___gxx_personality_v0
	.cfi_lsda 16, Lexception2
; %bb.0:
	sub	sp, sp, #48
	.cfi_def_cfa_offset 48
	stp	x20, x19, [sp, #16]             ; 16-byte Folded Spill
	stp	x29, x30, [sp, #32]             ; 16-byte Folded Spill
	add	x29, sp, #32
	.cfi_def_cfa w29, 16
	.cfi_offset w30, -8
	.cfi_offset w29, -16
	.cfi_offset w19, -24
	.cfi_offset w20, -32
	mov	x19, x0
	str	x0, [sp, #8]
Ltmp19:
	bl	__ZNSt3__119__thread_local_dataEv
Ltmp20:
; %bb.1:
	ldr	x1, [x19]
	str	xzr, [x19]
	ldr	x0, [x0]
Ltmp21:
	bl	_pthread_setspecific
Ltmp22:
; %bb.2:
	ldr	x8, [x19, #8]
Ltmp23:
	blr	x8
Ltmp24:
; %bb.3:
	ldr	x0, [x19]
	str	xzr, [x19]
	cbz	x0, LBB4_5
; %bb.4:
	bl	__ZNSt3__115__thread_structD1Ev
	bl	__ZdlPv
LBB4_5:
	mov	x0, x19
	bl	__ZdlPv
	mov	x0, #0
	ldp	x29, x30, [sp, #32]             ; 16-byte Folded Reload
	ldp	x20, x19, [sp, #16]             ; 16-byte Folded Reload
	add	sp, sp, #48
	ret
LBB4_6:
Ltmp25:
	mov	x19, x0
	add	x0, sp, #8
	bl	__ZNSt3__110unique_ptrINS_5tupleIJNS0_INS_15__thread_structENS_14default_deleteIS2_EEEEPFvvEEEENS3_IS8_EEED1B7v160006Ev
	mov	x0, x19
	bl	__Unwind_Resume
Lfunc_end2:
	.cfi_endproc
	.section	__TEXT,__gcc_except_tab
	.p2align	2, 0x0
GCC_except_table4:
Lexception2:
	.byte	255                             ; @LPStart Encoding = omit
	.byte	255                             ; @TType Encoding = omit
	.byte	1                               ; Call site Encoding = uleb128
	.uleb128 Lcst_end2-Lcst_begin2
Lcst_begin2:
	.uleb128 Ltmp19-Lfunc_begin2            ; >> Call Site 1 <<
	.uleb128 Ltmp24-Ltmp19                  ;   Call between Ltmp19 and Ltmp24
	.uleb128 Ltmp25-Lfunc_begin2            ;     jumps to Ltmp25
	.byte	0                               ;   On action: cleanup
	.uleb128 Ltmp24-Lfunc_begin2            ; >> Call Site 2 <<
	.uleb128 Lfunc_end2-Ltmp24              ;   Call between Ltmp24 and Lfunc_end2
	.byte	0                               ;     has no landing pad
	.byte	0                               ;   On action: cleanup
Lcst_end2:
	.p2align	2, 0x0
                                        ; -- End function
	.section	__TEXT,__text,regular,pure_instructions
	.private_extern	__ZNSt3__110unique_ptrINS_5tupleIJNS0_INS_15__thread_structENS_14default_deleteIS2_EEEEPFvvEEEENS3_IS8_EEED1B7v160006Ev ; -- Begin function _ZNSt3__110unique_ptrINS_5tupleIJNS0_INS_15__thread_structENS_14default_deleteIS2_EEEEPFvvEEEENS3_IS8_EEED1B7v160006Ev
	.globl	__ZNSt3__110unique_ptrINS_5tupleIJNS0_INS_15__thread_structENS_14default_deleteIS2_EEEEPFvvEEEENS3_IS8_EEED1B7v160006Ev
	.weak_def_can_be_hidden	__ZNSt3__110unique_ptrINS_5tupleIJNS0_INS_15__thread_structENS_14default_deleteIS2_EEEEPFvvEEEENS3_IS8_EEED1B7v160006Ev
	.p2align	2
__ZNSt3__110unique_ptrINS_5tupleIJNS0_INS_15__thread_structENS_14default_deleteIS2_EEEEPFvvEEEENS3_IS8_EEED1B7v160006Ev: ; @_ZNSt3__110unique_ptrINS_5tupleIJNS0_INS_15__thread_structENS_14default_deleteIS2_EEEEPFvvEEEENS3_IS8_EEED1B7v160006Ev
	.cfi_startproc
; %bb.0:
	stp	x20, x19, [sp, #-32]!           ; 16-byte Folded Spill
	.cfi_def_cfa_offset 32
	stp	x29, x30, [sp, #16]             ; 16-byte Folded Spill
	add	x29, sp, #16
	.cfi_def_cfa w29, 16
	.cfi_offset w30, -8
	.cfi_offset w29, -16
	.cfi_offset w19, -24
	.cfi_offset w20, -32
	mov	x19, x0
	ldr	x20, [x0]
	str	xzr, [x0]
	cbz	x20, LBB5_4
; %bb.1:
	ldr	x0, [x20]
	str	xzr, [x20]
	cbz	x0, LBB5_3
; %bb.2:
	bl	__ZNSt3__115__thread_structD1Ev
	bl	__ZdlPv
LBB5_3:
	mov	x0, x20
	bl	__ZdlPv
LBB5_4:
	mov	x0, x19
	ldp	x29, x30, [sp, #16]             ; 16-byte Folded Reload
	ldp	x20, x19, [sp], #32             ; 16-byte Folded Reload
	ret
	.cfi_endproc
                                        ; -- End function
	.private_extern	__ZNSt3__110unique_ptrINS_15__thread_structENS_14default_deleteIS1_EEED1B7v160006Ev ; -- Begin function _ZNSt3__110unique_ptrINS_15__thread_structENS_14default_deleteIS1_EEED1B7v160006Ev
	.globl	__ZNSt3__110unique_ptrINS_15__thread_structENS_14default_deleteIS1_EEED1B7v160006Ev
	.weak_def_can_be_hidden	__ZNSt3__110unique_ptrINS_15__thread_structENS_14default_deleteIS1_EEED1B7v160006Ev
	.p2align	2
__ZNSt3__110unique_ptrINS_15__thread_structENS_14default_deleteIS1_EEED1B7v160006Ev: ; @_ZNSt3__110unique_ptrINS_15__thread_structENS_14default_deleteIS1_EEED1B7v160006Ev
	.cfi_startproc
; %bb.0:
	stp	x20, x19, [sp, #-32]!           ; 16-byte Folded Spill
	.cfi_def_cfa_offset 32
	stp	x29, x30, [sp, #16]             ; 16-byte Folded Spill
	add	x29, sp, #16
	.cfi_def_cfa w29, 16
	.cfi_offset w30, -8
	.cfi_offset w29, -16
	.cfi_offset w19, -24
	.cfi_offset w20, -32
	mov	x19, x0
	ldr	x0, [x0]
	str	xzr, [x19]
	cbz	x0, LBB6_2
; %bb.1:
	bl	__ZNSt3__115__thread_structD1Ev
	bl	__ZdlPv
LBB6_2:
	mov	x0, x19
	ldp	x29, x30, [sp, #16]             ; 16-byte Folded Reload
	ldp	x20, x19, [sp], #32             ; 16-byte Folded Reload
	ret
	.cfi_endproc
                                        ; -- End function
	.p2align	2                               ; -- Begin function _Z8consumerv.cold.1
__Z8consumerv.cold.1:                   ; @_Z8consumerv.cold.1
	.cfi_startproc
; %bb.0:
	stp	x29, x30, [sp, #-16]!           ; 16-byte Folded Spill
	.cfi_def_cfa_offset 16
	mov	x29, sp
	.cfi_def_cfa w29, 16
	.cfi_offset w30, -8
	.cfi_offset w29, -16
Lloh12:
	adrp	x0, l___func__._Z8consumerv@PAGE
Lloh13:
	add	x0, x0, l___func__._Z8consumerv@PAGEOFF
Lloh14:
	adrp	x1, l_.str@PAGE
Lloh15:
	add	x1, x1, l_.str@PAGEOFF
Lloh16:
	adrp	x3, l_.str.1@PAGE
Lloh17:
	add	x3, x3, l_.str.1@PAGEOFF
	mov	w2, #17
	bl	___assert_rtn
	.loh AdrpAdd	Lloh16, Lloh17
	.loh AdrpAdd	Lloh14, Lloh15
	.loh AdrpAdd	Lloh12, Lloh13
	.cfi_endproc
                                        ; -- End function
	.globl	_data                           ; @data
.zerofill __DATA,__common,_data,4,2
	.globl	_ready                          ; @ready
.zerofill __DATA,__common,_ready,1,0
	.section	__TEXT,__cstring,cstring_literals
l___func__._Z8consumerv:                ; @__func__._Z8consumerv
	.asciz	"consumer"

l_.str:                                 ; @.str
	.asciz	"atomics.cpp"

l_.str.1:                               ; @.str.1
	.asciz	"data == 100"

l_.str.2:                               ; @.str.2
	.asciz	"thread constructor failed"

.subsections_via_symbols
