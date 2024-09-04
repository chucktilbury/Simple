/**
 * @file trace.h
 * @author Chuck Tilbury (chucktilbury@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-08-19
 * 
 * @copyright Copyright (c) 2024
 * 
 */
 #ifndef _TRACE_H_
 #define _TRACE_H_

typedef enum {
    TRACE_OFF,
    TRACE_ON,
} TraceState; 

#ifdef USE_TRACE 
#define INIT_TRACE() init_trace()
#define ENTER   trace_enter(__func__)
#define RET     do {trace_return(__func__, 0); return; } while(0)
#define RETURN(v) do { trace_return(__func__, (size_t)(v)); return (v); } while(0)
#define TRACE(fmt, ...) trace(__func__, fmt, ##__VA_ARGS__)
#define PUSH_TRACE_STATE(v) push_trace_state(v)
#define POP_TRACE_STATE() pop_trace_state()
#else
#define INIT_TRACE()
#define ENTER
#define RET     do { return; } while(0)
#define RETURN(v) do { return (v); } while(0)
#define TRACE(fmt, ...) 
#define PUSH_TRACE_STATE(v)
#define POP_TRACE_STATE()
#endif

void init_trace(void);
void trace_enter(const char* func);
void trace_return(const char* func, size_t val);
void trace(const char* func, const char* fmt, ...);
void push_trace_state(TraceState val);
TraceState pop_trace_state(void);

#endif /* _TRACE_H_ */

