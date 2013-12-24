#include <Cpu.hpp>
#include <BitUtils.hpp>
#include <Memory.hpp>
#include <Input.hpp>
#include <Video.hpp>
#include <Timers.hpp>

#include <glog/logging.h>
#include <stdlib.h>
#include <time.h>

namespace Chip8
{
    const std::string Cpu::_Tag = "Cpu:";

    Cpu::Cpu()
        : _pc(0),
          _sp(-1)
    {
        // Clear stack.
        for(int i = 0; i < 16; i++) {
            _stack[i] = 0;
        }

        // Seed random number generator
        srand(time(NULL));
    }

    Cpu & Cpu::instance()
    {
        static Cpu instance;
        return instance;
    }

    unsigned char Cpu::fetch()
    {
        // Read next memory address past the PC
        unsigned char byte = 0;
        if(!Memory::instance().read(_pc, byte)) {
            LOG(FATAL) << _Tag << "Failed to fetch next instruction at " << _pc;
        }
        _pc++;
        return byte;
}

    void Cpu::step()
    {
        unsigned char upper = fetch();
        unsigned char lower = fetch();
        LOG(INFO) << "Executing opcode " << (int) upper << " " << (int) lower;
        unsigned int address = extractAddress(upper, lower);
        unsigned char firstLevelOpcode = BitUtils::upper(upper);
        unsigned char lowerLower = BitUtils::lower(lower);
        unsigned char registerX = BitUtils::lower(upper);
        unsigned char registerY = BitUtils::upper(lower);
            
        unsigned char dataX = 0;
        unsigned char dataY = 0;
        unsigned char data0 = 0;

        if(!Memory::instance().getRegister(registerX, dataX)) {
            LOG(INFO) << _Tag << "Failed to get data in register " << (int) registerX;
        }
        if(!Memory::instance().getRegister(registerY, dataY)) {
            LOG(INFO) << _Tag << "Failed to get data in register " << (int) registerY;
        }
        if(!Memory::instance().getRegister(0x0, data0)) {
            LOG(INFO) << _Tag << "Failed to get data in register " << (int) 0x0;
        }

        switch(firstLevelOpcode) {
         case 0x0:
            switch(lower) {
                // CLEAR SCREEN 0x00E0 - Clears the screen to black.
                case 0xE0:
                    Video::instance().clearScreen();
                    break;
                // RETURN 0x00EE - Returns from a subroutine.
                case 0xEE:
                    ret();
                    break;
            }
            break;
         // JUMP 0x1NNN - Jumps to address NNN.
         case 0x1:
            jump(address);
            break;
         // CALL 0x2NNN - Calls the subroutine at address NNN.
         case 0x2:
            call(address);
            break;
         // SKIP IF EQUAL 0x3XNN - Skips the next instruction if VX == NN
         case 0x3:
            if(dataX == lower) {
                skipNextInstruction();
            }
            break;
         // SKIP IF EQUAL 0x4XNN - Skips the next instruction if VX == NN
         case 0x4:
            if(dataX != lower) {
                skipNextInstruction();
            }
            break;
         // SKIP IF REGISTER EQUAL 0x5XY0 - Skips the next instruction if VX == VY
         case 0x5:
            if(dataX == dataY) {
                skipNextInstruction();
            }
            break;
         // SET REGISTER 0x6xNN - Sets register VX to NN
         case 0x6:
            if(!Memory::instance().setRegister(registerX, lower)) {
                LOG(INFO) << _Tag << "Failed to set data " << lower << " in register " << (int) registerX;
            }
            break;
         // ADD 0x7XNN - Sets register VX = VX + NN
         case 0x7:
            {
                unsigned char result = dataX + lower;
                if(!Memory::instance().setRegister(registerX, result)) {
                    LOG(INFO) << _Tag << "Failed to set data " << result << " in register " << (int) registerX;
                }
            }
            break;
         case 0x8:
            switch(lowerLower) {
                 // LOAD VX, VY 0x8XY0 - Stores value of register VY in VX
                case 0x0:
                    if(!Memory::instance().setRegister(registerX, dataY))  {
                        LOG(INFO) << _Tag << "Failed to set data " << dataY << " in register " << (int) registerX;
                    }
                    break;
                // OR VX VY 0x8XY1 - Bitwise OR on VX and VY. Store result in VX
                case 0x1:
                    {
                        unsigned char resultOr = dataX | dataY;
                        if(!Memory::instance().setRegister(registerX, resultOr))  {
                            LOG(INFO) << _Tag << "Failed to set data " << resultOr << " in register " << (int) registerX;
                        }
                    }
                    break;
                // AND VX VY 0x8XY2 - Bitwise AND on VX and VY. Store result in VX
                case 0x2:
                    {
                        unsigned char resultAnd = dataX & dataY;
                        if(!Memory::instance().setRegister(registerX, resultAnd))  {
                            LOG(INFO) << _Tag << "Failed to set data " << resultAnd << " in register " << (int) registerX;
                        }
                    }
                    break;
                // XOR VX VY 0x8XY2 - Bitwise XOR on VX and VY. Store result in VX
                case 0x3:
                    {
                        unsigned char resultXor = dataX ^ dataY;
                        if(!Memory::instance().setRegister(registerX, resultXor))  {
                            LOG(INFO) << _Tag << "Failed to set data " << resultXor << " in register " << (int) registerX;
                        }
                    }
                    break;
                // ADD 0x8XY4 - Add VX to VY and store result in VX. If result is > 255
                //              set VF to 1, otherwise to 0.
                case 0x4:
                    {
                        unsigned char result = add(dataX, dataY);
                        if(!Memory::instance().setRegister(registerX, result))  {
                            LOG(INFO) << _Tag << "Failed to set data " << result << " in register " << (int) registerX;
                        }
                    }
                    break;
                // SUB 0x8XY5 - Subtract VY from VX and store result in VX. If VX > VY
                //              set VF to 1, otherwise to 0.
                case 0x5:
                    {
                        unsigned char result = sub(dataX, dataY);
                        if(!Memory::instance().setRegister(registerX, result))  {
                            LOG(INFO) << _Tag << "Failed to set data " << result << " in register " << (int) registerX;
                        }
                    }
                    break;
                // RIGHT SHIFT 0x8XY6 - If least significant bit of VX is 1 set VF to 1,
                //                      otherwise 0. Then right shift VX.
                case 0x6:
                    if(BitUtils::bitQuery(0x0, dataX) == 0x1) {
                        if(!Memory::instance().setRegister(0xF, 0x1))  {
                            LOG(INFO) << _Tag << "Could not set carry flag to 1";
                        }
                    } else {
                        if(!Memory::instance().setRegister(0xF, 0x0))  {
                            LOG(INFO) << _Tag << "Could not set carry flag to 0";
                        }
                    }
                    if(!Memory::instance().setRegister(registerX, dataX >> 1))  {
                        LOG(INFO) << _Tag << "Failed to set data " << dataX << " in register " << (int) registerX;
                    }
                    break;
                // SUB 0x8XY5 - Subtract VX from VY and store result in VX. If VY > VX
                //              set VF to 1, otherwise to 0.
                case 0x7:
                    {
                        unsigned char result = sub(dataY, dataX);
                        if(!Memory::instance().setRegister(registerX, result))  {
                            LOG(INFO) << _Tag << "Failed to set data " << result << " in register " << (int) registerX;
                        }
                    }
                    break;
                // LEFT SHIFT 0x8XYE - If most significant bit of VX is 1 set VF to 1,
                //                     otherwise 0. Then left shift VX.
                case 0xE:
                    if(BitUtils::bitQuery(0x7, dataX) == 0x1) {
                        if(!Memory::instance().setRegister(0xF, 0x1))  {
                            LOG(INFO) << _Tag << "Could not set carry flag to 1";
                        }
                    } else {
                        if(!Memory::instance().setRegister(0xF, 0x0))  {
                            LOG(INFO) << _Tag << "Could not set carry flag to 0";
                        }
                    }
                    if(!Memory::instance().setRegister(registerX, dataX << 1))  {
                        LOG(INFO) << _Tag << "Failed to set data " << dataX << " in register " << (int) registerX;
                    }
                    break;
                default:
                    LOG(INFO) << _Tag << "Unrecognized second level opcode " << (int) lowerLower << " for first level opcode " << (int) firstLevelOpcode;
                    break;
            }
            break;
         // SKIP IF VX VY NOT EQUAL 0x9XY0 - Skips the next instruction is VX != VY
         case 0x9:
            if(dataX != dataY) {
                skipNextInstruction();
            }
            break;
         // LOAD ADDRESS 0xANNN - Sets the value of register I to NNN
         case 0xA:
            LOG(INFO) << "Setting register I to " << address;
            Memory::instance().setI(address);
            break;
         // JUMP ADDRESS + V0 0xBNNN - Jumps to address + V0
         case 0xB:
            jump(address + data0);
            break;
         // RANDOM NUMBER 0xCXKK - Generate a random byte then and it with KK and store in VX
         case 0xC:
            {
                unsigned char random = randomByte();
                unsigned char resultAnd = random & lower;
                if(!Memory::instance().setRegister(registerX, resultAnd))  {
                    LOG(INFO) << _Tag << "Failed to set data " << resultAnd << " in register " << (int) registerX;
                }
                break;
            }
         // DRAW SPRITE 0xDXYN - Draws a sprite of height N at coordinate (X, Y). The sprite is loaded from memory address I.
         case 0xD:
         {
            // Read sprite from memory
            unsigned char n = BitUtils::lower(lower);
            LOG(INFO) << "Loading " << (int) n << " byte sprite from location " << Memory::instance().getI();
            unsigned char *sprite = new unsigned char[n];
            for(int i = 0; i < n; i++) {
                unsigned char data = 0;
                if(!Memory::instance().read(Memory::instance().getI() + i, data)) {
                    LOG(INFO) << _Tag << "Failed to read memory at address " << Memory::instance().getI() + i;
                }
                sprite[i] = data;
            }

            // Draw sprite onto screen
            Video::instance().drawSprite(dataX, dataY, sprite, n);
            delete[] sprite;
           
            break;
         }
         case 0xE:
            switch(lower) {
                // SKIP IF KEY PRESS = VX 0xEX9E - Skip the next instruction if the key with the value VX is pressed.
                case 0x9E:
                    if(!InputManager::instance().isValidKey(dataX)) {
                        LOG(INFO) << _Tag << dataX << " is not a valid key";
                        break;
                    }
                    if(InputManager::instance().isKeyDown(InputManager::Keys[dataX])) {
                        skipNextInstruction();
                    }
                    break;
                // SKIP IF KEY NOT PRESS = VX 0xEXA1 - Skip the next instruction if the key with the value VX is not pressed.
                case 0xA1:
                    if(!InputManager::instance().isValidKey(dataX)) {
                        LOG(INFO) << _Tag << dataX << " is not a valid key";
                        break;
                    }
                    if(!InputManager::instance().isKeyDown(InputManager::Keys[dataX])) {
                        skipNextInstruction();
                    }
                    break;
                default:
                    LOG(INFO) << _Tag << "Unrecognized second level opcode " << (int) lower << " for first level opcode " << (int) firstLevelOpcode;
                    break;
            }
            break;
         case 0xF:
            switch(lower) {
                // LOAD DELAY TIMER INTO REGISTER 0xFX07 - Loads the value of DT into VX.
                case 0x07:
                    if(!Memory::instance().setRegister(registerX, Timers::instance().getDelayTimer())) {
                        LOG(INFO) << _Tag << "Failed to set data " << Timers::instance().getDelayTimer() << " in register " << (int) registerX;
                    }
                    break;
                // WAIT FOR KEY PRESS - Wait for a key press, then store value of key in VX.
                case 0x0A:
                    {
                        unsigned char key = InputManager::instance().waitForKeyPress();
                        if(!Memory::instance().setRegister(registerX, key)){
                            LOG(INFO) << _Tag << "Failed to set data " << key << " in register " << (int) registerX;
                        }
                    }
                    break;
                // LOAD REGISTER INTO DELAY TIMER 0xFX15 - Loads the value in VX into DT.
                case 0x15:
                    Timers::instance().setDelayTimer(dataX);
                    break;
                // LOAD REGISTER INTO SOUND TIMER 0xFX18 - Loads the value in VX into ST.
                case 0x18:
                    Timers::instance().setSoundTimer(dataX);
                    break;
                // ADD ADDRESS, VX 0xFX1E - Add VX to I and store result in I.
                case 0x1E:
                    {
                        unsigned int result = Memory::instance().getI() + dataX;
                        LOG(INFO) << "Setting register I original = " << Memory::instance().getI() << " new = " << result;
                        Memory::instance().setI(result);
                    }
                    break;
                // LOAD FONT SPRITE ADDRESS 0xFX29 - Set I = address of Font VX.
                case 0x29:
                {
                    unsigned int fontAddress = Memory::instance().getFontAddress(dataX);
                    LOG(INFO) << "Font address for " << (int) dataX << " = " << fontAddress;
                    Memory::instance().setI(Memory::instance().getFontAddress(dataX));
                    break;
                }
                // BCD 0xFX33 - Convert VX to Binary Coded Decimal, then store result in I, I + 1, I + 2.
                case 0x33:
                    {
                        unsigned char hundreds = dataX / 100;
                        unsigned char tens = dataX % 100 / 10;
                        unsigned char ones = dataX % 100 % 10;
                        if(!Memory::instance().write(Memory::instance().getI(), hundreds)) {
                            LOG(INFO) << _Tag << "Failed to write data " << (int) hundreds << " to memory address " << address;
                        }
                        if(!Memory::instance().write(Memory::instance().getI() + 1, tens)) {
                            LOG(INFO) << _Tag << "Failed to write data " << (int) tens << " to memory address " << address;
                        }
                        if(!Memory::instance().write(Memory::instance().getI() + 2, ones)) {
                            LOG(INFO) << _Tag << "Failed to write data " << (int) ones << " to memory address " << address;
                        }
                    }
                    break;
                // LOAD REGISTER ARRAY TO MEMORY 0xFX55 - Load registers V0 - VX into memory starting at address I
                case 0x55:
                    for(unsigned char i = 0; i < registerX; i++) {
                        unsigned char data = 0;
                        if(!Memory::instance().getRegister(i, data)) {
                            LOG(INFO) << _Tag << "Failed to get data in register " << (int) i;
                        }
                        if(!Memory::instance().write(Memory::instance().getI() + i, data)) {
                            LOG(INFO) << _Tag << "Failed to write data " << (int) data << " to memory address " << Memory::instance().getI() + (unsigned int) i;
                        }
                    }
                    break;
                // LOAD MEMORY ARRAY INTO REGISTERS 0xFX65 - Load data starting at memory address I into registers V0 - VX.
                case 0x65:
                    for(unsigned char i = 0; i < registerX; i++) {
                        unsigned char data = 0;
                        if(!Memory::instance().read(Memory::instance().getI() + i, data)) {
                            LOG(INFO) << _Tag << "Failed to get data from memory address " << Memory::instance().getI() + (unsigned int) i;
                        }
                        if(!Memory::instance().setRegister(i, data)) {
                            LOG(INFO) << _Tag << "Failed to write data " << (int) data << " to register " << (int) i;
                        }
                    }
                    break;
                default:
                    LOG(INFO) << _Tag << "Unrecognized second level opcode " << (int) lower << " for first level opcode " << (int) firstLevelOpcode;
                    break;
            }
            break;
         default:
            LOG(INFO) << _Tag << "First level opcode not recognized " << (int) firstLevelOpcode;
            break;
        }
    }

    void Cpu::jump(unsigned int address)
    {
        LOG(INFO) << _Tag << "Jump to address " << address;
        _pc = address;
    }

    void Cpu::call(unsigned int address)
    {
        LOG(INFO) << _Tag << "Call subroutine at address " << address;
        _sp++;
        _stack[_sp] = _pc;
        jump(address);
    }

    void Cpu::ret()
    {
        LOG(INFO) << _Tag << "Return from subroutine ";
        jump(_stack[_sp]);
        _sp--;
    }

    void Cpu::skipNextInstruction()
    {
        LOG(INFO) << _Tag << "Skip next instruction";
        // Fetch next instruction but don't do anything with it.
        fetch();
        fetch();
    }
            
    unsigned char Cpu::add(unsigned char a, unsigned char b) const
    {
        unsigned int result = (unsigned int) a + (unsigned int) b;
        if(result > 0xFF) {
            // Carry occurred set the carry flag
            if(!Memory::instance().setRegister(0xF, 0x1)) {
                LOG(INFO) << _Tag << "Could not set carry flag to 1";
            }
        } else {
            // Carry did not occur set the carry flag
            if(!Memory::instance().setRegister(0xF, 0x0)) {
                LOG(INFO) << _Tag << "Could not set carry flag to 0";
            }
        }
        return result & 0xFF;
    }

    unsigned char Cpu::sub(unsigned char a, unsigned char b) const
    {
        int result = (int) a - (int) b;
        if(a > b) {
            // Set the NOT borrow flag
            if(!Memory::instance().setRegister(0xF, 0x1)) {
                LOG(INFO) << _Tag << "Could not set carry flag to 1";
            }
        } else {
            // Borrow occurred set the carry flag
            result = 0;
            if(!Memory::instance().setRegister(0xF, 0x0)) {
                LOG(INFO) << _Tag << "Could not set carry flag to 0";
            }
        }
        return result & 0xFF;
    }

    unsigned char Cpu::randomByte() const
    {
        return rand() % 256;
    }

    unsigned int Cpu::extractAddress(unsigned char upper, unsigned char lower)
    {
        return BitUtils::combine(BitUtils::lower(upper), lower);
    }
}
