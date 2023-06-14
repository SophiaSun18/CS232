RAM_SIZE = 1024


class RAM:
    def __init__(self, size=RAM_SIZE):
        self._minAddr = 0
        self._maxAddr = RAM_SIZE - 1
        self._memory = []   # a list of values.  Could be #s or instructions.
        for i in range(size):
            self._memory.append(0)

    def __getitem__(self, addr):
        return self._memory[addr]

    def __setitem__(self, addr, val):
        self._memory[addr] = val

    def is_legal_addr(self, addr):
        return self._minAddr <= addr <= self._maxAddr

class MMU:
    def __init__(self, ram):
        self.RAM = ram
        self.reloc = 0
        self.limit = 0

    def __getitem__(self, addr):
        new_addr = self.addr_translation(addr)
        return self.RAM[new_addr]
    
    def __setitem__(self, addr, val):
        new_addr = self.addr_translation(addr)
        self.RAM[new_addr] = val
    
    def set_reloc_register(self, val):
        self.reloc = val
    
    def set_limit_register(self, val):
        self.limit = val
    
    def addr_translation(self, addr):
        if (self.addr_check(addr)):
            new_addr = addr + self.reloc
            return new_addr
        else:
            print("Error: Bad Address {}: too high!!!".format(addr))
            return 0
            
    def addr_check(self, addr):
        if addr > self.limit:
            return False
        else:
            return True