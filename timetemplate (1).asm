  # timetemplate.asm
  # Written 2015 by F Lundevall
  # Copyright abandonded - this file is in the public domain.

.macro	PUSH (%reg)
	addi	$sp,$sp,-4
	sw	%reg,0($sp)
.end_macro

.macro	POP (%reg)
	lw	%reg,0($sp)
	addi	$sp,$sp,4
.end_macro

	.data
	.align 2
mytime:	.word 0x5957
timstr:	.ascii "text more text lots of text\0"
	.text
	
main:
	# print timstr
	la	$a0,timstr
	li	$v0,4
	syscall
	nop
	# wait a little
	li	$a0,2
	jal	delay
	nop
	# call tick
	la	$a0,mytime
	jal	tick
	nop
	# call your function time2string
	la	$a0,timstr
	la	$t0,mytime
	lw	$a1,0($t0)
	jal	time2string
	nop
	# print a newline
	li	$a0,10
	li	$v0,11
	syscall
	nop
	# go back and do it all again
	j	main
	nop
# tick: update time pointed to by $a0
tick:	lw	$t0,0($a0)	# get time
	addiu	$t0,$t0,1	# increase
	andi	$t1,$t0,0xf	# check lowest digit
	sltiu	$t2,$t1,0xa	# if digit < a, okay
	bnez	$t2,tiend
	nop
	addiu	$t0,$t0,0x6	# adjust lowest digit
	andi	$t1,$t0,0xf0	# check next digit
	sltiu	$t2,$t1,0x60	# if digit < 6, okay
	bnez	$t2,tiend
	nop
	addiu	$t0,$t0,0xa0	# adjust digit
	andi	$t1,$t0,0xf00	# check minute digit
	sltiu	$t2,$t1,0xa00	# if digit < a, okay
	bnez	$t2,tiend
	nop
	addiu	$t0,$t0,0x600	# adjust digit
	andi	$t1,$t0,0xf000	# check last digit
	sltiu	$t2,$t1,0x6000	# if digit < 6, okay
	bnez	$t2,tiend
	nop
	addiu	$t0,$t0,0xa000	# adjust last digit
tiend:	sw	$t0,0($a0)	# save updated result
	jr	$ra		# return
	nop

  # you can write your code for subroutine "hexasc" below this line
  #
  
 
time2string:
PUSH $ra


addi $t4,$0,0xf #make $t4 mask 1111


#first mask digi
and $t3,$a1,$t4 #masked out put binary 4 lsb t3 binary output
#put last a0 to the stack so we can put current t3 into hexasc
PUSH $a0
move $a0,$t3
jal hexasc #v0  is output
POP $a0
move $s3,$v0
sll $t4,$t4,4

#second mask digi
and $t3,$a1,$t4 #masked out put binary 4 lsb
#put last a0 to the stack so we can put current t3 into hexasc
PUSH $a0
move $a0,$t3
srl $a0,$a0,4
jal hexasc #v0  is output
POP $a0
move $s2,$v0
sll $t4,$t4,4


#third mask digi
and $t3,$a1,$t4 #masked out put binary 4 lsb
#put last a0 to the stack so we can put current t3 into hexasc
PUSH $a0
move $a0,$t3
srl $a0,$a0,8
jal hexasc #v0  is output
POP $a0
move $s1,$v0
sll $t4,$t4,4

#forth mask digi
and $t3,$a1,$t4 #masked out put binary 4 lsb
#put last a0 to the stack so we can put current t3 into hexasc
PUSH $a0
move $a0,$t3
srl $a0,$a0,12
jal hexasc #v0  is output
POP $a0
move $s0,$v0
sll $t4,$t4,4
########

 
#initialized a0 (try)
addi $a0,$0,0x0

addi $t5,$0,0

addi $t8,$0,0x00

clean:
nop
sb $t8,timstr($t5)
addi $t5,$t5,1
slti $t6,$t5,28
bne  $t6,0,clean

# load : and null to s4 and s5
addi $s4,$0,0x3a
addi $s5,$0,0x00
#store bites and ready to print (a0)
addi $t5,$0,0 #reset index

sb $s0,timstr($t5)
addi $s0,$0,0x0
addi $t5,$t5,1
sb $s1,timstr($t5)
addi $s1,$0,0x0
addi $t5,$t5,1

sb $s4,timstr($t5)
addi $s4,$0,0x0
addi $t5,$t5,1

sb $s2,timstr($t5)
addi $s2,$0,0x0
addi $t5,$t5,1

sb $s3,timstr($t5)
addi $s3,$0,0x0
addi $t5,$t5,1

sb $s5,timstr($t5)
addi $s5,$0,0x0


POP $ra
jr $ra

hexasc:
andi $a0,$a0,0xf #4LSB
slti $t0,$a0,10
beq $t0,1,load9
nop
beq $t0,0,loadA
nop

load9:
addi $v0,$a0,0x30
jr $ra
loadA:
addi $a0,$a0,-10
addi $v0,$a0,0x41
jr $ra
delay:
 jr $ra
 nop
 stop:
 nop
