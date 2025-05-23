struct registers_t {
    unsigned int gs;
    unsigned int fs;
    unsigned int es;
    unsigned int ds;
    unsigned int edi;
    unsigned int esi;
    unsigned int ebp;
    unsigned int esp;   // original esp (before pusha)
    unsigned int ebx;
    unsigned int edx;
    unsigned int ecx;
    unsigned int eax;
};
