/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect2.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mipang <mipang@student.42.fr>              #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-10-06 13:35:22 by mipang            #+#    #+#             */
/*   Updated: 2026-10-06 13:35:22 by mipang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vect2.hpp"

vect2::vect2(){x = 0; y = 0;}

vect2::vect2(int x,int y){
	this->x = x;
	this->y = y;
}

vect2::vect2(const vect2& other)
{
	this->x = other.x;
	this->y = other.y;
}

vect2 vect2::operator+(const vect2& other) const
{
	vect2	result;
	result.x = this->x + other.x;
	result.y = this->y + other.y;
	return(result);
}

vect2 vect2::operator-(const vect2& other) const
{
	vect2	result;
	result.x = this->x - other.x;
	result.y = this->y - other.y;
	return(result);
}

vect2 vect2::operator-() const
{
	vect2	result;
	result.x = -x;
	result.y = -y;
	return(result);
}

vect2& vect2::operator+=(const vect2& other)
{
	this->x += other.x;
	this->y += other.y;
	return (*this);
}

vect2& vect2::operator-=(const vect2& other)
{
	this->x -= other.x;
	this->y -= other.y;
	return (*this);

}

vect2& vect2::operator*=(int m)
{
	this->x *= m;
	this->y *= m;
	return (*this);
}

vect2& vect2::operator++()
{
	this->x += 1;
	this->y += 1;
	return *this;
}

vect2 vect2::operator++(int)
{
	vect2	old(*this);

	this->x++;
	this->y++;
	return old;
}

vect2& vect2::operator--()
{
	this->x -= 1;
	this->y -= 1;
	return *this;
}

vect2 vect2::operator--(int)
{
	vect2	old(*this);

	this->x--;
	this->y--;
	return old;
}

vect2 vect2::operator*(int m) const
{
	vect2 result;

	result.x = this->x * m;
	result.y = this->y * m;
	return result;
}

vect2& vect2::operator=(const vect2& other)
{
	this->x = other.x;
	this->y = other.y;
	return (*this);
}

bool vect2::operator!=(const vect2& other) const
{
	return ((x != other.x) || (y != other.y));
}

bool vect2::operator==(const vect2& other) const
{
	return ((x == other.x) && (y== other.y));
}

int vect2::operator[](int i) const
{
	if (i == 0)
		return (x);
	return (y);
}

int& vect2::operator[](int i)
{
	if (i == 0)
		return (x);
	return (y);
}

std::ostream& operator<<(std::ostream& os, const vect2& v)
{
	os << "{" << v[0] << ", " << v[1] << "}";
	return (os);
}

vect2 operator*(int i, const vect2& other)
{
	return (other * i);
}
