#ifndef TIMELOGS_H
#define TIMELOGS_H

#include <vector>

#include "Timelog.h"

class TimelogsData : public QObject
{
    Q_OBJECT

    using Timelogs = std::vector<Timelog>;
public:
    TimelogsData() = default;

    // std vector methods
    Timelogs::const_iterator begin() const;
    Timelogs::const_iterator end() const;
    Timelogs::iterator begin();
    Timelogs::iterator end();
    int size() const;
    void clear();
    const Timelog& operator[](int idx) const;
    const Timelog& front() const;
    const Timelog& back() const;


    // my methods
    void add(const Timelog& log);
    void remove(int id);
    Timelog* timelog(int id);
    std::optional<Timelogs::iterator> contains(int id);
    int index(Timelogs::iterator iter) const;

signals:
    void preLogAdded(int index);
    void postLogAdded();
    void preLogRemoved(int index);
    void postLogRemoved();

private:
    Timelogs::iterator findTimelog(int id);

private:
    Timelogs timelogs_;
};

#endif // TIMELOGS_H
