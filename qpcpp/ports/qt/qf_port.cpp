//****************************************************************************
// Product: QF/C++ port to Qt
// Last Updated for Version: QP 5.1.1/Qt 5.1.1
// Date of the Last Update:  Nov 05, 2013
//
//                    Q u a n t u m     L e a P s
//                    ---------------------------
//                    innovating embedded systems
//
// Copyright (C) 2002-2013 Quantum Leaps, LLC. All rights reserved.
//
// This program is open source software: you can redistribute it and/or
// modify it under the terms of the GNU General Public License as published
// by the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Alternatively, this program may be distributed and modified under the
// terms of Quantum Leaps commercial licenses, which expressly supersede
// the GNU General Public License and are specifically designed for
// licensees interested in retaining the proprietary status of their code.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program. If not, see <http://www.gnu.org/licenses/>.
//
// Contact information:
// Quantum Leaps Web sites: http://www.quantum-leaps.com
//                          http://www.state-machine.com
// e-mail:                  info@quantum-leaps.com
//****************************************************************************
#include <QtWidgets>
//-----------------
#include "qf_pkg.h"
#include "aothread.h"
#include "tickerthread.h"
#include "qassert.h"

Q_DEFINE_THIS_MODULE("qf_port")

//****************************************************************************
namespace QP {

//............................................................................
QMutex QF_qtMutex_;

//............................................................................
static TickerThread l_tickerThread;

//............................................................................
void QF_enterCriticalSection() { QF_qtMutex_.lock();   }
void QF_leaveCriticalSection() { QF_qtMutex_.unlock(); }

//............................................................................
AOThread::~AOThread() {
    wait();
}
//............................................................................
void AOThread::run() {
    Q_REQUIRE(m_act != static_cast<void *>(0));
    QP::QF::thread_(static_cast<QP::QActive *>(m_act));
}

//****************************************************************************
TickerThread::~TickerThread() {
    wait();
}
//............................................................................
void TickerThread::run() {
    m_isRunning = true;
    do {
        msleep(m_tickInterval);
        QP::QF_onClockTick();
#ifdef Q_SPY
        QP::QS_onEvent();
#endif
    } while (m_isRunning);
}

//............................................................................
void QF::init(void) {
}
//............................................................................
int16_t QF::run(void) {
    onStartup();                                // invoke the startup callback

    l_tickerThread.setStackSize(1024U*4U);                     // 4KB of stack
    l_tickerThread.start();

    // run the Qt event loop (console or GUI)
    return static_cast<int16_t>(QCoreApplication::instance()->exec());
}
//............................................................................
void QF::thread_(QActive *act) {
    QThread::Priority qt_prio = QThread::IdlePriority;
    switch (act->m_prio) {              // remap QF priority to Win32 priority
        case 1:
            qt_prio = QThread::IdlePriority;
            break;
        case 2:
            qt_prio = QThread::LowestPriority;
            break;
        case 3:
            qt_prio = QThread::LowPriority;
            break;
        case (QF_MAX_ACTIVE - 2):
            qt_prio = QThread::HighPriority;
            break;
        case (QF_MAX_ACTIVE - 1):
            qt_prio = QThread::HighestPriority;
            break;
        case QF_MAX_ACTIVE:
            qt_prio = QThread::TimeCriticalPriority;
            break;
        default:
            qt_prio = QThread::NormalPriority;
            break;
    }

    AOThread *thread = static_cast<AOThread *>(act->m_thread);
    thread->setPriority(qt_prio);
    thread->m_isRunning = true;
    do {                  // loop until m_thread is cleared in QActive::stop()
        QEvt const *e = act->get_();                         // wait for event
        act->dispatch(e);     // dispatch to the active object's state machine
        gc(e);          // check if the event is garbage, and collect it if so
    } while (thread->m_isRunning);

    QF::remove_(act);
    delete thread;
    delete act->m_osObject;
}
//............................................................................
void QF::stop(void) {
    l_tickerThread.m_isRunning = false;
}
//............................................................................
void QF_setTickRate(unsigned ticksPerSec) {
    l_tickerThread.m_tickInterval = 1000U/ticksPerSec;
}
//............................................................................
void QActive::start(uint8_t prio,
                    QEvt const **qSto, uint32_t qLen,
                    void *stkSto, uint32_t stkSize,
                    QEvt const *ie)
{
    Q_REQUIRE(stkSto == static_cast<void *>(0));          // no per-task stack

    m_thread   = new AOThread(this);
    m_osObject = new QWaitCondition;
    m_eQueue.init(qSto, qLen);
    m_prio = prio;

    QF::add_(this);                     // make QF aware of this active object
    init(ie);                                // execute the initial transition

    QS_FLUSH();                          // flush the trace buffer to the host

    AOThread *thread = static_cast<AOThread *>(m_thread);
    thread->setStackSize(stkSize);
    thread->start();
}
//............................................................................
void QActive::stop(void) {
    Q_REQUIRE(m_thread != 0);
    static_cast<AOThread *>(m_thread)->m_isRunning = false;
}

}                                                              // namespace QP
