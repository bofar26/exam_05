/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect2.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mipang <mipang@student.42.fr>              #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-10-06 14:03:35 by mipang            #+#    #+#             */
/*   Updated: 2026-10-06 14:03:35 by mipang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECT2_HPP
#define VECT2_HPP

#include <iostream>

class vect2{
	private:
		int	x;
		int	y;
	public:
		vect2(int x,int y);
		vect2();
		vect2(const vect2& other);
		vect2 operator+(const vect2& other) const;
		vect2 operator-(const vect2& other) const;
		vect2 operator-() const;
		vect2& operator+=(const vect2& other);
		vect2& operator-=(const vect2& other);
		vect2& operator*=(int m);
		vect2& operator++();
		vect2 operator++(int);
		vect2& operator--();
		vect2 operator--(int);
		vect2 operator*(int m) const;
		vect2& operator=(const vect2& other);
		int operator[](int i) const;
		int& operator[](int i);
		bool operator!=(const vect2& other) const;
		bool operator==(const vect2& other) const;
};

std::ostream& operator<<(std::ostream& os, const vect2& v);
vect2 operator*(int i, const vect2& other);

# endif
