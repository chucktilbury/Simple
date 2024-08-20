
project(common)

include(${PROJECT_SOURCE_DIR}/../../BuildOpts.txt)

add_library(${PROJECT_NAME} STATIC
    buffer.c        
    cmderrors.c     
    cmdline.c       
    cmdparse.c      
    hash.c         
    memory.c        
    ptr_lst.c       
    str.c           
    str_lst.c
    trace.c
    llist.c
)


