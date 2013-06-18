#ifndef ERCV_GLOBAL_H
#define ERCV_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(ERCV_LIBRARY)
#  define ERCVSHARED_EXPORT Q_DECL_EXPORT
#else
#  define ERCVSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // ERCV_GLOBAL_H
