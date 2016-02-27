  # labwork.S
  # Written 2015 by F Lundevall
  # Skeleton file for IS1200/IS1500 lab 1 2015-2016.
  # The macros PUSH and POP are in the public domain.
.macro	PUSH reg
	addi	$sp,$sp,-4
	sw	\reg,0($sp)
.endm

.macro	POP reg
	lw	\reg,0($sp)
	addi	$sp,$sp,4
.endm

  # You can add your own code here
  #
.global  enable_interrupt

enable_interrupt:
ei 
j $ra
nop

.global time2string

time2string:
PUSH $ra

PUSH $s0
PUSH $s1
PUSH $s2
PUSH $s3
PUSH $s4
PUSH $s5
PUSH $s6
PUSH $s7

addi $t4,$0,0xf #make $t4 mask 1111


#first mask digi
and $t3,$a1,$t4 #masked out put binary 4 lsb t3 binary output
#put last a0 to the stack so we can put current t3 into hexasc
PUSH $a0
move $a0,$t3
jal hexasc #v0  is output
nop
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
nop
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
nop
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
nop
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
sb $t8,textstring($t5)
addi $t5,$t5,1
slti $t6,$t5,28
bne  $t6,0,clean
nop




# load : and null to s4 and s5
addi $s4,$0,0x3a
addi $s5,$0,0x00
#store bites and ready to print (a0)
addi $t5,$0,0 #reset index

sb $s0,textstring($t5)
addi $s0,$0,0x0
addi $t5,$t5,1
sb $s1,textstring($t5)
addi $s1,$0,0x0
addi $t5,$t5,1

sb $s4,textstring($t5)
addi $s4,$0,0x0
addi $t5,$t5,1

sb $s2,textstring($t5)
addi $s2,$0,0x0
addi $t5,$t5,1

beq $s3,0x32,special

sb $s3,textstring($t5)
addi $s3,$0,0x0
addi $t5,$t5,1

sb $s5,textstring($t5)
addi $s5,$0,0x0


POP $s7
POP $s6
POP $s5
POP $s4
POP $s3
POP $s2
POP $s1
POP $s0

POP $ra
jr $ra
nop



special:
addi $s3,$0,0x54
addi $s5,$0,0x57
addi $s6,$0,0x4f
addi $s7,$0,0x00


sb $s3,textstring($t5)
addi $s3,$0,0x0
addi $t5,$t5,1

sb $s5,textstring($t5)
addi $s5,$0,0x0
addi $t5,$t5,1
sb $s6,textstring($t5)
addi $s6,$0,0x0
addi $t5,$t5,1
sb $s7,textstring($t5)
addi $s7,$0,0x0
addi $t5,$t5,1


POP $s7
POP $s6
POP $s5
POP $s4
POP $s3
POP $s2
POP $s1
POP $s0

POP $ra
jr $ra
nop


.global hexasc
hexasc:
andi $a0,$a0,0xf #4LSB
slti $t0,$a0,10
beq $t0,1,load9
nop
beq $t0,0,loadA
nop

.global load9
load9:
addi $v0,$a0,0x30
jr $ra
nop

.global loadA
loadA:
addi $a0,$a0,-10
addi $v0,$a0,0x41
jr $ra
nop


.global delay

delay:
PUSH $s1
li $a1,2500 #a1 =ms number behind is input value
#while loop
while:

slti $t0,$a1,1 # if ms bigger than 1 $t0 boolean algebra
addi $s1,$0,0x0
bne $t0,1,whileloop #if  invert 1 because of slt
nop
jr $ra
nop

.global whileloop
whileloop:
addi $a1,$a1,-1
#for loop
addi $s1,$0,0 #int i =1 initialization    i =t0 for for loop after
for:
slti $t1,$s1,4711 #i smaller than 4711 t1 bollean algebra non invert
bne $t1,0,forloop
nop
POP $s1
j while
nop

.global forloop
forloop:
addi $s1,$s1,1
nop
j for
nop




