#ifndef DIAG_H
#define DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

// debug flags
#define	DIAGFL_OBJ_F8		0x0001F800				// Anybus obhect 0xF8 = Host Ethernet IP object, all CIP messages
#define	DIAGFL_CIP_CFG		0x00018000
#define	DIAGFL_CIP_ROUTE	0x00014000
#define	DIAGFL_CIP_OBJ		0x00012000
#define	DIAGFL_CIP_FILE		0x00011000
#define	DIAGFL_CIP_NVS		0x00010800
#define DIAGFL_OBJ_10		0x00020000				// Anybus object 0x10 = ABCC file system interface
#define DIAGFL_OBJ_F9		0x00040000				// Anybus object 0x10 = ABCC file system interface
#define	DIAGFL_OBJ_ANY		0x00080000				// any (other) message

#ifdef DEBUG
// Debugging enabled
#  if defined(__SUNPRO_C) || defined(__SUNPRO_CC)
	 // use variadic macros
     void diag_printf(const char* file, const char* func, int line, const char* fmt, ...);
     void diag_printf_nt(const char* fmt, ...);
#    define DIAG(format...) { diag_printf(__FILE__, __FUNCTION__, __LINE__ , format, ##__VA_ARGS__); }
#    define DIAG_NT(format...) { diag_printf_nt(format, ##__VA_ARGS__); }
#  elif defined(__BORLANDC__) && (__BORLANDC__ < 0x0700 )
	 // fu***** old BCC does not provide variadic macros
#    define DIAG logger("\n"); dumptick(); logger
#    define DIAG_NT logger
#  else
     // assume standards compliant compiler (C99)
     void diag_printf(const char* file, const char* func, int line, const char* fmt, ...);
     void diag_printf_nt(const char* fmt, ...);
     unsigned int diag_getflag(void);
     void diag_setflag(unsigned int flag);
     void diag_resetflag(unsigned int flag);
     unsigned int diag_getflag(void);
#    define DIAG(format, arg...) diag_printf("", __FUNCTION__, __LINE__, format, ## arg)
#    define DIAG_FL(lvl, format, arg...) if ((lvl)&diag_getflag()) diag_printf("", __FUNCTION__, __LINE__, format, ## arg)
#    define DIAG_NT(format, arg...) diag_printf_nt(format, ## arg)
#    define DIAG_SETFL(x) diag_setflag(x)
#    define DIAG_RESFL(x) diag_resetflag(x)
#  endif
#else
// No Debugging
#  if defined(__SUNPRO_C) || defined(__SUNPRO_CC)
#    define DIAG(format...) do {} while (0)
#  elif defined(__BORLANDC__) && (__BORLANDC__ < 0x0700 )
#    define DIAG diag_noprintf
#    define DIAG_NT diag_noprintf
#  else // standard conformant compiler (C99)
#    define DIAG(format, arg...) do {} while (0)
#    define DIAG_FL(lvl, format, arg...) do {} while (0)
#    define DIAG_NT(format, arg...)  do {} while (0)
#  endif
#  define DIAG_SETFL(x) do {} while (0)
#  define DIAG_RESFL(x) do {} while (0)
#endif

#ifdef __cplusplus
}
#endif

#endif // DIAG_H
