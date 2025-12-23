global load_pde
load_pde:
    mov eax, [esp+4] ;; first argument (pd address)
    mov cr3, eax 
    ret
    
global enable_paging
enable_paging:
    mov eax, cr0
    or eax, 0x80000000 ; bit 31
    mov cr0, eax
    hlt
    ret