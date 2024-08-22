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

#ifdef USE_TRACE 
#define ENTER   trace_enter(__func__)
#define RET     trace_return(__func__, 0)
#define RETURN(v) do { trace_return(__func__, (size_t)(v)); return (v); } while(0)
#define TRACE_STATE(s) trace_state(__func__, (s))
#define TRACE(fmt, ...) trace(__func__, fmt, ##__VA_ARGS__)
#else
#define ENTER
#define RET
#define RETURN(v) do { return (v); } while(0)
#define TRACE_STATE(s)
#define TRACE(fmt, ...) 
#endif

void trace_enter(const char* func);
void trace_return(const char* func, size_t val);
void trace_state(const char* func, int state);
void trace(const char* func, const char* fmt, ...);

#endif /* _TRACE_H_ */

