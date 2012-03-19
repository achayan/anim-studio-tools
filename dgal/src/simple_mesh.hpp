#ifndef _DGAL_SIMPLE_MESH__H_
#define _DGAL_SIMPLE_MESH__H_

#include <vector>
#include <OpenEXR/ImathVec.h>
#include <boost/mpl/bool.hpp>
#include "adaptors/mesh_points.hpp"


namespace dgal {

	/*
	 * @class mesh
	 * @brief A very simple mesh representation.
	 */
	template<typename T>
	struct simple_mesh
	{
		typedef T							point_type;
		typedef unsigned int				index_type;
		typedef typename T::BaseType		scalar_type;
		typedef std::vector<T>				points_vector;
		typedef std::vector<index_type>		polygon_type;
		typedef std::vector<polygon_type>	polygon_vector;

		void clear() {
			m_points.clear();
			m_polys.clear();
		}

		inline unsigned int numPoints() const { return m_points.size(); }
		inline unsigned int numPolys() const { return m_polys.size(); }

		template<typename Points>
		void setPoints(const Points& points);

		template<typename Points>
		void appendPoly(const Points& poly);

		void appendPoly(const std::vector<index_type>& poly) { m_polys.push_back(poly); }

		void setMesh(const simple_mesh<T>& rhs) { *this = rhs; }

		template<typename Mesh>
		void setMesh(const Mesh& rhs);

		points_vector	m_points;
		polygon_vector	m_polys;
	};

	template<typename T>
	struct is_simple_mesh : public boost::mpl::false_{};

	template<typename T>
	struct is_simple_mesh<simple_mesh<T> > : public boost::mpl::true_{};


///////////////////////// impl

template<typename T>
template<typename Points>
void simple_mesh<T>::setPoints(const Points& points)
{
	typedef points_adaptor<Points> Adaptor;

	Adaptor a(points);
	unsigned int npoints = a.size();

	m_points.resize(npoints);
	for(unsigned int i=0; i<npoints; ++i)
		m_points[i] = a[i];
}


template<typename T>
template<typename Points>
void simple_mesh<T>::appendPoly(const Points& poly)
{
	typedef points_adaptor<Points> Adaptor;

	Adaptor a(poly);

	m_polys.push_back(polygon_type());
	polygon_type& destPoly = m_polys.back();

	unsigned int nverts = a.size();
	destPoly.resize(nverts);
	for(unsigned int i=0; i<nverts; ++i)
		destPoly[i] = a.index(i);
}


template<typename T>
template<typename Mesh>
void simple_mesh<T>::setMesh(const Mesh& rhs)
{
	typedef mesh_adaptor<Mesh> Adaptor;

	setPoints(mesh_points<Mesh>(rhs));

	Adaptor a(rhs);
	unsigned int npolys = a.numPolys();
	m_polys.clear();
	m_polys.reserve(npolys);

	for(unsigned int i=0; i<npolys; ++i)
		appendPoly(a.getPoly(i));
}

}

#endif

















/***
    Copyright 2008-2012 Dr D Studios Pty Limited (ACN 127 184 954) (Dr. D Studios)

    This file is part of anim-studio-tools.

    anim-studio-tools is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    anim-studio-tools is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with anim-studio-tools.  If not, see <http://www.gnu.org/licenses/>.
***/
