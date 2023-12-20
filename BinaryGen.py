def toBinary(num):
    return format(int(num.strip("$t")), '05b')

def convert_instruction_to_binary(instruction):
    opcode_table = {
        'add':   '000000',
        'div':   '000000',
        'mult':  '000000',
        'sub':   '000000',
        'or':    '000000',
        'and':   '000000',
        'neq':   '000000',
        'lt':    '000000',
        'gt':    '000000',
        'comp':  '000000',
        'get' :  '000000',
        'let':   '000000',
        'lw':    '000001',
        'sw':    '000010',
        'addi':  '000011',
        'subi':  '000100',
        'beq':   '000101',
        'j':     '001001',
        'jr' :   '001010',
        'jal':   '001011',
        'input': '001100',
        'output':'001101',
        'NextLineTBE':'001110',
        'changeOffset':'001111',
        'changeROM':'010000',
        'setProcessLine': '010001',
        'ProcessCheck': '010010',
        'setQuantum': '010011',
        'halt': '111111'
    }
    funct_table = {
        'div':  '100000',
        'mult':  '000001',
        'sub':  '000010',
        'add':  '000011',
        'or':  '000100',
        'and':  '000101',
        'lt':  '000110',
        'let':  '000111',
        'gt':  '001000',
        'get':  '001001',
        'comp':  '001010',
        'neq':  '001011'
    }
    instr_parts = instruction.split()
    instr_type = instr_parts[0]

    if instr_type in ['addi', 'subi', 'lw', 'sw','beq']:
        opcode = opcode_table[instr_type]
        rs = toBinary(instr_parts[2])
        rt = toBinary(instr_parts[1])
        immediate = format(int(instr_parts[3].strip("$t")), '016b')
        binary_instr = f'{opcode}{rs}{rt}{immediate}'

    elif instr_type in ['jr']:
        opcode = opcode_table[instr_type]
        rs = toBinary(instr_parts[1])
        immediate = format(0, '021b')
        binary_instr = f'{opcode}{rs}{immediate}'
    elif instr_type in ['changeOffset']:
        opcode = opcode_table[instr_type]
        rs = toBinary(instr_parts[1])
        rt = toBinary(instr_parts[2])
        immediate = format(0, '016b')
        binary_instr = f'{opcode}{rs}{rt}{immediate}'

    elif instr_type in ['j', 'jal']:
        opcode = opcode_table[instr_type]
        address = format(int(instr_parts[1].strip("$t")), '026b')
        binary_instr = f'{opcode}{address}'
    elif instr_type in ['halt','NextLineTBE','changeROM']:
        opcode = opcode_table[instr_type]
        address = "0"*26
        binary_instr = f'{opcode}{address}'
    elif instr_type in ['input', 'output', 'setProcessLine','ProcessCheck','setQuantum']:
        opcode = opcode_table[instr_type]
        rs = toBinary(instr_parts[1])
        immediate = format(0, '021b')
        binary_instr = f'{opcode}{rs}{immediate}'
    else:
        opcode = opcode_table[instr_type]
        funct = funct_table[instr_type]
        rs = toBinary(instr_parts[2])
        rt = toBinary(instr_parts[3])
        rd = toBinary(instr_parts[1])
        shamt = '00000'
        binary_instr = f'{opcode}{rs}{rt}{rd}{shamt}{funct}'

    return binary_instr

asm = open("test.asmfinal","r")
commands = []
for line in asm:
    line = line.replace("\n","")
    commands.append(line)

binary = open("rom.txt","w")
for command in commands:
    binario = convert_instruction_to_binary(command)
    binary.write(str(binario)+"\n")
binary.close()