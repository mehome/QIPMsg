// This file is part of QIpMsg.
//
// QIpMsg is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// QIpMsg is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with QIpMsg.  If not, see <http://www.gnu.org/licenses/>.
//

#ifndef MSG_THREAD_H
#define MSG_THREAD_H

#include "msg.h"

#include <QThread>
#include <QMutex>

class MsgServer;

class MsgThread : public QThread
{
    Q_OBJECT

public:
    friend class MsgServer;
    MsgThread(QObject *parent = 0) :QThread(parent) {}
    ~MsgThread();

    virtual void run();

    void addSendMsg(Msg msg);
    void addSendMsgNotLock(Msg msg);
    void removeSendMsg(QString packetNo);
    void removeSendMsgNotLock(QString packetNo);

    bool isBounded() const;

private slots:
    void exitOnError(QString s);

signals:
    void newMsg(Msg msg);
    void newUserMsg(Msg msg);

private:
    QMutex m_lock;
    QMap<QString, Msg> m_sendMsgMap;

    MsgServer *m_msgServer;
};

#endif // !MSG_THREAD_H

