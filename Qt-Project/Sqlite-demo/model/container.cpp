#include "container.h"

Container::Container()
{

}

Container::Container(QString ContainerId,QString Name,QString State,QString Image,QString Port,QString Command)
{
    this->ContainerId = ContainerId;
    this->Name = Name;
    this->State = State;
    this->Image = Image;
    this->Port = Port;
    this->Command = Command;
}

QString Container::GetContainerId()
{
    return this->ContainerId;
}

void Container::SetContainerId(QString ContainerId)
{
    this->ContainerId = ContainerId;
}

QString Container::GetName()
{
    return this->Name;
}

void Container::SetName(QString Name)
{
    this->Name = Name;
}

QString Container::GetState()
{
    return this->State;
}

void Container::SetState(QString State)
{
    this->State = State;
}

QString Container::GetImage()
{
    return this->Image;
}

void Container::SetImage(QString Image)
{
    this->Image = Image;
}

QString Container::GetPort()
{
    return this->Port;
}

void Container::SetPort(QString Port)
{
    this->Port = Port;
}

QString Container::GetCommand()
{
    return this->Command;
}

void Container::SetCommand(QString Command)
{
    this->Command = Command;
}
