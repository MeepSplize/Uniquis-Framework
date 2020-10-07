#include "pch.h"

#include "Toolkit\\Math\\Curve.h"

template<unsigned __int8 Dimension>
Uniquis::Curve<Dimension>::Curve()
{

}

template<unsigned __int8 Dimension>
Uniquis::Curve<Dimension>::~Curve()
{

}

template<unsigned __int8 Dimension>
Uniquis::Vector<Dimension> Uniquis::Curve<Dimension>::interpolate(const float interpolation)
{
	float TemporaryStorage = (1 - interpolation);

	Vector<Dimension> InterpolatedPoint((                                                         (TemporaryStorage * TemporaryStorage * TemporaryStorage) * this->vAnchorPoints[0])  + 
										(((3 *  interpolation) *                                  (TemporaryStorage * TemporaryStorage))                   * this->vControlPoints[0]) + 
										(((3 * (interpolation  * interpolation)) *                 TemporaryStorage)                                       * this->vControlPoints[1]) + 
										(      (interpolation  * interpolation   * interpolation)                                                          * this->vAnchorPoints[1]));

	return std::move(InterpolatedPoint);
}

template class Uniquis::Curve<2>;
template class Uniquis::Curve<3>;