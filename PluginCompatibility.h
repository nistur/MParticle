#ifndef __PLUGIN_COMPATIBILITY_H__
#define __PLUGIN_COMPATIBILITY_H__

#ifndef MPLUGIN_DECLARE
#   ifndef MPLUGIN_EXPORT
#      ifdef WIN32
#         include <windows.h>
#         define MPLUGIN_EXPORT __declspec(dllexport)
#      else
#         define MPLUGIN_EXPORT
#      endif /*WIN32*/
#   endif/*MPLUGIN_EXPORT*/
#   define MPLUGIN_DECLARE(name) \
  MPLUGIN_EXPORT void StartPlugin();
  MPLUGIN_EXPORT void EndPlugin();
#endif/*MPLUGIN_DECLARE*/

#ifndef MPLUGIN_START_IMPLEMENT
#   define MPLUGIN_START_IMPLEMENT(name) \
  void StartPlugin()
#endif

#ifndef MPLUGIN_END_IMPLEMENT
#   define MPLUGIN_END_IMPLEMENT(name) \
  void EndPlugin()
#endif

#endif/*__PLUGIN_COMPATIBILITY_H__*/
