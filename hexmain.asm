  # hexmain.asm
  # Written 2015-09-04 by F Lundevall
  # Copyright abandonded - this file is in the public domain.
  
	.text
main:
	li	$a0,8	# change this to test different values

	jal	hexasc		# call hexasc
	nop			# delay slot filler (just in case)	
	move	$a0,$v0		# copy return value to argument register

	li	$v0,11		# syscall with v0 = 11 will print out
	syscall			# one byte from a0 to the Run I/O window
	
stop:	j	stop		# stop after one run
	nop			# delay slot filler (just in case)

  # You can write your own code for hexasc here
  #
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

done:

