;Configurações do ambiente do compilador
list p=16f819
	#include <p16f819.inc>

;Configurações internas co PIC
	__config _INTRC_IO & _WDT_OFF & _PWRTE_ON & _MCLR_OFF & _BODEN_OFF & _LVP_OFF & _CPD_OFF & _WRT_OFF  & _DEBUG_OFF & _CCP1_RB2 & _CP_OFF

;;;;;;;Inicio do codigo fonte;;;;;; 
; Botão
	#define		Button	PORTA,RA0
	
;Reset
 org  H'0000'
 goto inicio

;Interrupções
 org	H'0004'
 retfie

inicio:
  
; Variavel Contadora
	cblock 0x20         ;Determina o endereco
	Cont                ;Determina o nome
	Endc                ;Fim da declaracao
	movlw H'1'          ;Seta 0 em W
	movwf Cont          ;Copia de W para Cont

; Desabilita entradas analogicas
	BANKSEL 	ADCON1        ; Seleciona o Banco do ADCON1
	MOVLW 		0x06         ; Configure all pins
	MOVWF 		ADCON1        ; as digital inputs

; Configura PortB como saida	
	BANKSEL		TRISB     ;Seleciona o Banco do PORTB
	movlw		H'00'       ;Seta 0 em W
	movwf		TRISB       ;Copia de W para TRISB

; Configura PortA como entrada	
	BANKSEL		TRISA     ;Seleciona o Banco do TRISA
	movlw		H'FF'       ;Seta FF em W
	movwf		TRISA       ;Copia de W para TRISA

;Loop infinito
	BANKSEL 	PORTB     ;Retorno ao banco inicial
	CLRF 		PORTB       ;Zerando PortB
	call 		Print0      ;Chama subrotina de impresão

Loop:
	btfsc		Button      ;Verifica acionamento do botão
	call 		incremento  ;Chama subrotina de incremento
	goto		Loop        ;Volta ao Loop
	

;subrotina de soma
incremento:
	btfsc		Button        ;Verifica acionamento do botão
	goto 		incremento        ;Aguarda o fim do acionamento
	call		Print        ;chama subrotina de impresao
	incf		Cont        ;Incremento do contador
	return

;subrotina de impresao
Print:	
	movlw		D'0'        ;Valor de referencia
	subwf		Cont,w      ;Subtração comparativa
	btfsc		STATUS,2    ;Verificação da comparação
	call 		Print0      ;Impreção no display 7seg

	movlw		D'1'        ;Valor de referencia
	subwf		Cont,w      ;Subtração comparativa
	btfsc		STATUS,2    ;Verificação da comparação
	call 		Print1      ;Impreção no display 7seg

	movlw		D'2'        ;Valor de referencia
	subwf		Cont,w      ;Subtração comparativa
	btfsc		STATUS,2    ;Verificação da comparação
	call 		Print2      ;Impreção no display 7seg
	
	movlw		D'3'        ;Valor de referencia
	subwf		Cont,w      ;Subtração comparativa
	btfsc		STATUS,2    ;Verificação da comparação
	call 		Print3      ;Impreção no display 7seg

	movlw		D'4'        ;Valor de referencia
	subwf		Cont,w      ;Subtração comparativa
	btfsc		STATUS,2    ;Verificação da comparação
	call 		Print4      ;Impreção no display 7seg

	movlw		D'5'        ;Valor de referencia
	subwf		Cont,w      ;Subtração comparativa
	btfsc		STATUS,2    ;Verificação da comparação
	call 		Print5      ;Impreção no display 7seg

	movlw		D'6'        ;Valor de referencia
	subwf		Cont,w      ;Subtração comparativa
	btfsc		STATUS,2    ;Verificação da comparação
	call 		Print6      ;Impreção no display 7seg

	movlw		D'7'        ;Valor de referencia
	subwf		Cont,w      ;Subtração comparativa
	btfsc		STATUS,2    ;Verificação da comparação
	call 		Print7      ;Impreção no display 7seg

	movlw		D'8'        ;Valor de referencia
	subwf		Cont,w      ;Subtração comparativa
	btfsc		STATUS,2    ;Verificação da comparação
	call 		Print8      ;Impreção no display 7seg

	movlw		D'9'        ;Valor de referencia
	subwf		Cont,w      ;Subtração comparativa
	btfsc		STATUS,2    ;Verificação da comparação
	call 		Print9      ;Impreção no display 7seg

	movlw		D'10'       ;Valor de referencia
	subwf		Cont,w      ;Subtração comparativa
	btfsc		STATUS,2    ;Verificação da comparação
	call 		Print10     ;Impreção no display 7seg
	return	

Print0:
	movlw		B'00111111' ;Valor binario para impresão	
	movwf		PORTB       ;Enviando valor da porta
	return                      ;Retorno do chamado

Print1:
	movlw		B'00000110' ;Valor binario para impresão	
	movwf		PORTB       ;Enviando valor da porta
	return                      ;Retorno do chamado

Print2:
	movlw		B'01011011' ;Valor binario para impresão	
	movwf		PORTB       ;Enviando valor da porta
	return                      ;Retorno do chamado

Print3:
	movlw		B'01001111' ;Valor binario para impresão	
	movwf		PORTB       ;Enviando valor da porta
	return                      ;Retorno do chamado

Print4:
	movlw		B'01100110' ;Valor binario para impresão	
	movwf		PORTB       ;Enviando valor da porta
	return                      ;Retorno do chamado

Print5:
	movlw		B'01101101' ;Valor binario para impresão	
	movwf		PORTB       ;Enviando valor da porta
	return                      ;Retorno do chamado

Print6:
	movlw		B'01111101' ;Valor binario para impresão	
	movwf		PORTB       ;Enviando valor da porta
	return                      ;Retorno do chamado

Print7:
	movlw		B'00100111' ;Valor binario para impresão	
	movwf		PORTB       ;Enviando valor da porta
	return                      ;Retorno do chamado

Print8:
	movlw		B'01111111' ;Valor binario para impresão	
	movwf		PORTB       ;Enviando valor da porta
	return                      ;Retorno do chamado

Print9:
	movlw		B'01101111' ;Valor binario para impresão	
	movwf		PORTB       ;Enviando valor da porta
	return                      ;Retorno do chamado

Print10:
	movlw		D'0'        ;Valor inicial da contagem
	movwf		Cont        ;Voltando ao valor inicial
	call 		Print0      ;chama subrotina de impresao
	return                      ;Retorno do chamado

;Fim	
	end                         ;Fim da execução
