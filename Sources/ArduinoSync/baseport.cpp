//
//
//  Generated by StarUML(tm) C++ Add-In
//
//  @ Project : Core Model
//  @ File Name : baseport.cpp
//  @ Date : 4/12/2013
//  @ Author : 
//
//


#include "baseport.h"
#include "portsettings.h"
#include <QtCore/QStringList>


BasePort::BasePort()
{

	m_Ready = false;
}

bool BasePort::init()
{
	readSettings();
	m_Ready = initPort();
	return m_Ready;
}

void BasePort::readSettings()
{
	m_PortSettingsReader.readSettings(m_fileName);
}

bool BasePort::initPort()
{
	const PortSettings* settings = m_PortSettingsReader.getSettings();

	if(settings == NULL)
		return false;
	m_port.setPortName(settings->getPort());
	if(m_port.open(settings->getIOMode()))
	{
		if(!m_port.setBaudRate(settings->getRate()))
			return false;
		if(!m_port.setDataBits((QSerialPort::DataBits)settings->getDataBits()))
			return false;
		if(!m_port.setParity((QSerialPort::Parity)settings->getParity()))
			return false;
		if(!m_port.setStopBits((QSerialPort::StopBits)settings->getStopBits()))
			return false;
		if(!m_port.setFlowControl((QSerialPort::FlowControl)settings->getFlowControl()))
			return false;

		connect(&m_port, SIGNAL(readyRead()),
			this, SLOT(readReadyData()));

		return true;
	}
	auto error = m_port.errorString();
	return false;
	
}

void BasePort::setPort( QString& port )
{
	m_port.setPortName(port);
}

BasePort::~BasePort()
{
	m_port.close();
}

void BasePort::setBufferSize( int size )
{
	m_port.setReadBufferSize(size);
	m_BufferSize = size;
}

int BasePort::getBufferSize() const
{
	return m_port.readBufferSize();
}

void BasePort::readReadyData()
{
	auto resp = m_port.readAll();
	m_tempData += QString(resp);
	findCommands();
}

void BasePort::findCommands()
{
	if(m_tempData.indexOf(";") == -1)
		return;
	QStringList commands = m_tempData.split(";");
	if(!commands.count() )
		return;
	for(auto i = 0; i < commands.count() - 1; i++)
	{
		m_queue.enqueue(commands[i]);
		emit readyRead();
	}
	if(!commands[commands.count() - 1].isEmpty())
	{
		m_tempData = commands[commands.count() -1];		
	}
	else
		m_tempData = "";
	m_queue.clear();
}


