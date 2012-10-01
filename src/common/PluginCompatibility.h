#ifndef __PLUGIN_COMPATIBILITY_H__
#define __PLUGIN_COMPATIBILITY_H__

#include <MEngine.h>

#ifdef MPLUGIN_AVAILABLE
# ifdef MINGED_ENGINE
#  include <MMIngEdPlugin.h>
# else
#  include <MPlugin.h>
# endif/*MINGED_ENGINE*/
#else
# ifndef MPLUGIN_DECLARE
#  ifndef MPLUGIN_EXPORT
#   ifdef WIN32
#    include <windows.h>
#    define MPLUGIN_EXPORT __declspec(dllexport)
#   else
#    define MPLUGIN_EXPORT
#   endif /*WIN32*/
#  endif/*MPLUGIN_EXPORT*/
#  define MPLUGIN_DECLARE(name)			\
   MPLUGIN_EXPORT void StartPlugin();
   MPLUGIN_EXPORT void EndPlugin();
# endif/*MPLUGIN_DECLARE*/
#endif/*MPLUGIN_AVAILABLE*/

#ifndef MINGED_PLUGIN_DECLARE
# define MINGED_PLUGIN_DECLARE(name)		\
    MPLUGIN_DECLARE(name)
#endif

#ifndef MPLUGIN_START_IMPLEMENT
# define MPLUGIN_START_IMPLEMENT(name)		\
  void StartPlugin()
#endif/*MPLUGIN_START_IMPLEMENT*/

#ifndef MINGED_PLUGIN_START_IMPLEMENT
# define MINGED_PLUGIN_START_IMPLEMENT(name)	\
  MPLUGIN_START_IMPLEMENT(name)
#endif/*MINGED_PLUGIN_START_IMPLEMENT*/

#ifndef MPLUGIN_END_IMPLEMENT
# define MPLUGIN_END_IMPLEMENT(name)		\
  void EndPlugin()
#endif/*MPLUGIN_END_IMPLEMENT*/

#ifndef MINGED_PLUGIN_END_IMPLEMENT
# define MINGED_PLUGIN_END_IMPLEMENT(name)	\
    MPLUGIN_END_IMPLEMENT(name)
#endif/*MINGED_PLUGIN_END_IMPLEMENT*/

#endif/*__PLUGIN_COMPATIBILITY_H__*/
