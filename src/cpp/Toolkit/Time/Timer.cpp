#include "pch.h"

#include "Toolkit\\Time\\Timer.h"

Uniquis::Timer::Timer() 

	: Timepoint(std::chrono::steady_clock::now()) 
{

}

Uniquis::Timer::~Timer() 
{

}

void Uniquis::Timer::reset() noexcept 
{
	this->Timepoint = std::chrono::steady_clock::now();
}

std::chrono::duration<float> Uniquis::Timer::getDuration() noexcept 
{
	return (std::chrono::steady_clock::now() - this->Timepoint);
}

std::chrono::steady_clock::time_point Uniquis::Timer::getTimepoint() noexcept 
{
	return this->Timepoint;
}