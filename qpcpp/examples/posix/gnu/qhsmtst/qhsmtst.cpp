//****************************************************************************
// Model: qhsmtst.qm
// File:  ./qhsmtst.cpp
//
// This code has been generated by QM tool (see state-machine.com/qm).
// DO NOT EDIT THIS FILE MANUALLY. All your changes will be lost.
//
// This program is open source software: you can redistribute it and/or
// modify it under the terms of the GNU General Public License as published
// by the Free Software Foundation.
//
// This program is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
// or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
// for more details.
//****************************************************************************
// @(/2/1) ...................................................................
#include "qp_port.h"
#include "qhsmtst.h"

namespace QHSMTST {

// @(/1/0) ...................................................................
class QHsmTst : public QP::QHsm {
private:
    bool m_foo;

public:
    QHsmTst()
      : QHsm(Q_STATE_CAST(&QHsmTst::initial))
    {}

protected:
    static QP::QState initial(QHsmTst * const me, QP::QEvt const * const e);
    static QP::QState s(QHsmTst * const me, QP::QEvt const * const e);
    static QP::QState s1(QHsmTst * const me, QP::QEvt const * const e);
    static QP::QState s11(QHsmTst * const me, QP::QEvt const * const e);
    static QP::QState s2(QHsmTst * const me, QP::QEvt const * const e);
    static QP::QState s21(QHsmTst * const me, QP::QEvt const * const e);
    static QP::QState s211(QHsmTst * const me, QP::QEvt const * const e);
};


static QHsmTst l_hsmtst; // the only instance of the QHsmTst class

// global-scope definitions -----------------------------------------
QP::QHsm * const the_hsm = &l_hsmtst; // the opaque pointer

// @(/1/0) ...................................................................

// @(/1/0/2) .................................................................
// @(/1/0/2/0)
QP::QState QHsmTst::initial(QHsmTst * const me, QP::QEvt const * const e) {
    (void)e; // avoid compiler warning
    me->m_foo = 0U;
    BSP_display("top-INIT;");
    return Q_TRAN(&QHsmTst::s2);
}
// @(/1/0/2/1) ...............................................................
QP::QState QHsmTst::s(QHsmTst * const me, QP::QEvt const * const e) {
    QP::QState status_;
    switch (e->sig) {
        // @(/1/0/2/1)
        case Q_ENTRY_SIG: {
            BSP_display("s-ENTRY;");
            status_ = Q_HANDLED();
            break;
        }
        // @(/1/0/2/1)
        case Q_EXIT_SIG: {
            BSP_display("s-EXIT;");
            status_ = Q_HANDLED();
            break;
        }
        // @(/1/0/2/1/0)
        case Q_INIT_SIG: {
            BSP_display("s-INIT;");
            status_ = Q_TRAN(&QHsmTst::s11);
            break;
        }
        // @(/1/0/2/1/1)
        case I_SIG: {
            // @(/1/0/2/1/1/0)
            if (me->m_foo) {
                me->m_foo = 0U;
                BSP_display("s-I;");
                status_ = Q_HANDLED();
            }
            else {
                status_ = Q_UNHANDLED();
            }
            break;
        }
        // @(/1/0/2/1/2)
        case E_SIG: {
            BSP_display("s-E;");
            status_ = Q_TRAN(&QHsmTst::s11);
            break;
        }
        // @(/1/0/2/1/3)
        case TERMINATE_SIG: {
            BSP_terminate(0);
            status_ = Q_HANDLED();
            break;
        }
        default: {
            status_ = Q_SUPER(&QP::QHsm::top);
            break;
        }
    }
    return status_;
}
// @(/1/0/2/1/4) .............................................................
QP::QState QHsmTst::s1(QHsmTst * const me, QP::QEvt const * const e) {
    QP::QState status_;
    switch (e->sig) {
        // @(/1/0/2/1/4)
        case Q_ENTRY_SIG: {
            BSP_display("s1-ENTRY;");
            status_ = Q_HANDLED();
            break;
        }
        // @(/1/0/2/1/4)
        case Q_EXIT_SIG: {
            BSP_display("s1-EXIT;");
            status_ = Q_HANDLED();
            break;
        }
        // @(/1/0/2/1/4/0)
        case Q_INIT_SIG: {
            BSP_display("s1-INIT;");
            status_ = Q_TRAN(&QHsmTst::s11);
            break;
        }
        // @(/1/0/2/1/4/1)
        case I_SIG: {
            BSP_display("s1-I;");
            status_ = Q_HANDLED();
            break;
        }
        // @(/1/0/2/1/4/2)
        case D_SIG: {
            // @(/1/0/2/1/4/2/0)
            if (!me->m_foo) {
                me->m_foo = true;
                BSP_display("s1-D;");
                status_ = Q_TRAN(&QHsmTst::s);
            }
            else {
                status_ = Q_UNHANDLED();
            }
            break;
        }
        // @(/1/0/2/1/4/3)
        case A_SIG: {
            BSP_display("s1-A;");
            status_ = Q_TRAN(&QHsmTst::s1);
            break;
        }
        // @(/1/0/2/1/4/4)
        case B_SIG: {
            BSP_display("s1-B;");
            status_ = Q_TRAN(&QHsmTst::s11);
            break;
        }
        // @(/1/0/2/1/4/5)
        case F_SIG: {
            BSP_display("s1-F;");
            status_ = Q_TRAN(&QHsmTst::s211);
            break;
        }
        // @(/1/0/2/1/4/6)
        case C_SIG: {
            BSP_display("s1-C;");
            status_ = Q_TRAN(&QHsmTst::s2);
            break;
        }
        default: {
            status_ = Q_SUPER(&QHsmTst::s);
            break;
        }
    }
    return status_;
}
// @(/1/0/2/1/4/7) ...........................................................
QP::QState QHsmTst::s11(QHsmTst * const me, QP::QEvt const * const e) {
    QP::QState status_;
    switch (e->sig) {
        // @(/1/0/2/1/4/7)
        case Q_ENTRY_SIG: {
            BSP_display("s11-ENTRY;");
            status_ = Q_HANDLED();
            break;
        }
        // @(/1/0/2/1/4/7)
        case Q_EXIT_SIG: {
            BSP_display("s11-EXIT;");
            status_ = Q_HANDLED();
            break;
        }
        // @(/1/0/2/1/4/7/0)
        case H_SIG: {
            BSP_display("s11-H;");
            status_ = Q_TRAN(&QHsmTst::s);
            break;
        }
        // @(/1/0/2/1/4/7/1)
        case D_SIG: {
            // @(/1/0/2/1/4/7/1/0)
            if (me->m_foo) {
                me->m_foo = false;
                BSP_display("s11-D;");
                status_ = Q_TRAN(&QHsmTst::s1);
            }
            else {
                status_ = Q_UNHANDLED();
            }
            break;
        }
        // @(/1/0/2/1/4/7/2)
        case G_SIG: {
            BSP_display("s11-G;");
            status_ = Q_TRAN(&QHsmTst::s211);
            break;
        }
        default: {
            status_ = Q_SUPER(&QHsmTst::s1);
            break;
        }
    }
    return status_;
}
// @(/1/0/2/1/5) .............................................................
QP::QState QHsmTst::s2(QHsmTst * const me, QP::QEvt const * const e) {
    QP::QState status_;
    switch (e->sig) {
        // @(/1/0/2/1/5)
        case Q_ENTRY_SIG: {
            BSP_display("s2-ENTRY;");
            status_ = Q_HANDLED();
            break;
        }
        // @(/1/0/2/1/5)
        case Q_EXIT_SIG: {
            BSP_display("s2-EXIT;");
            status_ = Q_HANDLED();
            break;
        }
        // @(/1/0/2/1/5/0)
        case Q_INIT_SIG: {
            BSP_display("s2-INIT;");
            status_ = Q_TRAN(&QHsmTst::s211);
            break;
        }
        // @(/1/0/2/1/5/1)
        case I_SIG: {
            // @(/1/0/2/1/5/1/0)
            if (!me->m_foo) {
                me->m_foo = true;
                BSP_display("s2-I;");
                status_ = Q_HANDLED();
            }
            else {
                status_ = Q_UNHANDLED();
            }
            break;
        }
        // @(/1/0/2/1/5/2)
        case F_SIG: {
            BSP_display("s2-F;");
            status_ = Q_TRAN(&QHsmTst::s11);
            break;
        }
        // @(/1/0/2/1/5/3)
        case C_SIG: {
            BSP_display("s2-C;");
            status_ = Q_TRAN(&QHsmTst::s1);
            break;
        }
        default: {
            status_ = Q_SUPER(&QHsmTst::s);
            break;
        }
    }
    return status_;
}
// @(/1/0/2/1/5/4) ...........................................................
QP::QState QHsmTst::s21(QHsmTst * const me, QP::QEvt const * const e) {
    QP::QState status_;
    switch (e->sig) {
        // @(/1/0/2/1/5/4)
        case Q_ENTRY_SIG: {
            BSP_display("s21-ENTRY;");
            status_ = Q_HANDLED();
            break;
        }
        // @(/1/0/2/1/5/4)
        case Q_EXIT_SIG: {
            BSP_display("s21-EXIT;");
            status_ = Q_HANDLED();
            break;
        }
        // @(/1/0/2/1/5/4/0)
        case Q_INIT_SIG: {
            BSP_display("s21-INIT;");
            status_ = Q_TRAN(&QHsmTst::s211);
            break;
        }
        // @(/1/0/2/1/5/4/1)
        case G_SIG: {
            BSP_display("s21-G;");
            status_ = Q_TRAN(&QHsmTst::s1);
            break;
        }
        // @(/1/0/2/1/5/4/2)
        case A_SIG: {
            BSP_display("s21-A;");
            status_ = Q_TRAN(&QHsmTst::s21);
            break;
        }
        // @(/1/0/2/1/5/4/3)
        case B_SIG: {
            BSP_display("s21-B;");
            status_ = Q_TRAN(&QHsmTst::s211);
            break;
        }
        default: {
            status_ = Q_SUPER(&QHsmTst::s2);
            break;
        }
    }
    return status_;
}
// @(/1/0/2/1/5/4/4) .........................................................
QP::QState QHsmTst::s211(QHsmTst * const me, QP::QEvt const * const e) {
    QP::QState status_;
    switch (e->sig) {
        // @(/1/0/2/1/5/4/4)
        case Q_ENTRY_SIG: {
            BSP_display("s211-ENTRY;");
            status_ = Q_HANDLED();
            break;
        }
        // @(/1/0/2/1/5/4/4)
        case Q_EXIT_SIG: {
            BSP_display("s211-EXIT;");
            status_ = Q_HANDLED();
            break;
        }
        // @(/1/0/2/1/5/4/4/0)
        case H_SIG: {
            BSP_display("s211-H;");
            status_ = Q_TRAN(&QHsmTst::s);
            break;
        }
        // @(/1/0/2/1/5/4/4/1)
        case D_SIG: {
            BSP_display("s211-D;");
            status_ = Q_TRAN(&QHsmTst::s21);
            break;
        }
        default: {
            status_ = Q_SUPER(&QHsmTst::s21);
            break;
        }
    }
    return status_;
}


} // namespace QHSMTST
