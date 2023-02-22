#ifndef MTABLEVIEWPRIVATE_P_H
#define MTABLEVIEWPRIVATE_p_H

#include "mtableview.h"
#include <DObjectPrivate>

DCORE_USE_NAMESPACE

class MTableViewPrivate : public DObjectPrivate
{
public:
    MTableViewPrivate(MTableView *qq);
    ~MTableViewPrivate();

    void init();

    D_DECLARE_PUBLIC(MTableView)
};

#endif // MTABLEVIEWPRIVATE_P_H
