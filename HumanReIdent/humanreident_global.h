#ifndef HUMANREIDENT_GLOBAL_H
#define HUMANREIDENT_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef HUMANREIDENT_LIB
# define HUMANREIDENT_EXPORT Q_DECL_EXPORT
#else
# define HUMANREIDENT_EXPORT Q_DECL_IMPORT
#endif

#endif // HUMANREIDENT_GLOBAL_H
