/***********************************************************
     Starter code for Assignment 3

     This code was originally written by Jack Wang for
		    CSC418, SPRING 2005

		implements scene_object.h

***********************************************************/

#include <cmath>
#include <iostream>
#include "scene_object.h"

bool UnitSquare::intersect( Ray3D& ray, const Matrix4x4& worldToModel,
		const Matrix4x4& modelToWorld ) {
	// TODO: implement intersection code for UnitSquare, which is
	// defined on the xy-plane, with vertices (0.5, 0.5, 0), 
	// (-0.5, 0.5, 0), (-0.5, -0.5, 0), (0.5, -0.5, 0), and normal
	// (0, 0, 1).
	//
	// Your goal here is to fill ray.intersection with correct values
	// should an intersection occur.  This includes intersection.point, 
	// intersection.normal, intersection.none, intersection.t_value.   
	//
	// HINT: Remember to first transform the ray into object space  
	// to simplify the intersection test.

	// transform the ray into object space
	Ray3D tf_ray (worldToModel * ray.origin, worldToModel * ray.dir);
	// Recall that the parametric curve of a line is given by 
	// p = origin + t * dir
	// Therefore, to compute the point of intersection with the xy plane,
	// we start by finding the value of t that satisfies:
	double t = - tf_ray.origin[2] / tf_ray.dir[2];
	
	// directly return false if the value of t is smaller than 0 
	// because this implies that ray is shooting in the wrong direction
	if (t < 0)
	{
		return false;
	}
	
	double x = tf_ray.origin[0] + t * tf_ray.dir[0];
	double y = tf_ray.origin[1] + t * tf_ray.dir[1];
	
	if (x >= -0.5 && x <= 0.5 && y >= -0.5 && y <= 0.5)
	{
		if (!ray.intersection.none && ray.intersection.t_value < t)
		{
			return false;
		}
		
		Vector3D norm = transNorm(worldToModel, Vector3D(0, 0, 1));
		
		norm.normalize();
		
		// transform everything back to the world coordinate
		ray.intersection.point  = modelToWorld * Point3D(x, y, 0);
		ray.intersection.normal = norm;
		ray.intersection.none = false;
		ray.intersection.t_value = t;
		
		return true;
	}
	else
	{
		return false;
	}
}

bool UnitSphere::intersect( Ray3D& ray, const Matrix4x4& worldToModel,
		const Matrix4x4& modelToWorld ) {
	// TODO: implement intersection code for UnitSphere, which is centred 
	// on the origin.  
	//
	// Your goal here is to fill ray.intersection with correct values
	// should an intersection occur.  This includes intersection.point, 
	// intersection.normal, intersection.none, intersection.t_value.   
	//
	// HINT: Remember to first transform the ray into object space  
	// to simplify the intersection test.
	
	// again, transform the ray into object space
	Ray3D tf_ray (worldToModel * ray.origin, worldToModel * ray.dir);
	// Since the equation of a unit sphere is given by 
	// x ^ 2 + y ^ 2 + z ^ 2 = 1
	// which therefore implies that we need to solve for the quadratic equation
	// (tf_ray.origin[0] + t * tf_ray.dir[0]) ^ 2 + 
	// (tf_ray.origin[1] + t * tf_ray.dir[1]) ^ 2 + 
	// (tf_ray.origin[2] + t * tf_ray.dir[2]) ^ 2 = 1
	// After simplification, we get
	double A = 
		tf_ray.dir[0] * tf_ray.dir[0] + 
		tf_ray.dir[1] * tf_ray.dir[1] + 
		tf_ray.dir[2] * tf_ray.dir[2];
	double B = 
		2 * tf_ray.origin[0] * tf_ray.dir[0] + 
		2 * tf_ray.origin[1] * tf_ray.dir[1] + 
		2 * tf_ray.origin[2] * tf_ray.dir[2];
	double C = 
		tf_ray.origin[0] * tf_ray.origin[0] + 
		tf_ray.origin[1] * tf_ray.origin[1] + 
		tf_ray.origin[2] * tf_ray.origin[2] - 1;
	
	double det = B * B - 4 * A * C;
	
	if (det < 0)
	{
		return false;
	}
	double t_1 = (- B - std::sqrt(det)) / (2 * A);
	double t_2 = (- B + std::sqrt(det)) / (2 * A);
	
	if (t_1 < 0 && t_2 < 0)
	{
		return false;
	}
	if (t_1 < 0)
	{
		if (!ray.intersection.none && ray.intersection.t_value < t_2)
		{
			return false;
		}
		
		double x = tf_ray.origin[0] + t_2 * tf_ray.dir[0];
		double y = tf_ray.origin[1] + t_2 * tf_ray.dir[1];
		double z = tf_ray.origin[2] + t_2 * tf_ray.dir[2];
		
		Vector3D norm = transNorm(worldToModel, Vector3D(x, y, z));
		
		norm.normalize();
		
		// transform everything back to the world coordinate
		ray.intersection.point  = modelToWorld * Point3D(x, y, z);
		ray.intersection.normal = norm;
		ray.intersection.none = false;
		ray.intersection.t_value = t_2;
		
		return true;
	}
	if (t_2 < 0)
	{
		if (!ray.intersection.none && ray.intersection.t_value < t_1)
		{
			return false;
		}
		
		double x = tf_ray.origin[0] + t_1 * tf_ray.dir[0];
		double y = tf_ray.origin[1] + t_1 * tf_ray.dir[1];
		double z = tf_ray.origin[2] + t_1 * tf_ray.dir[2];
		
		Vector3D norm = transNorm(worldToModel, Vector3D(x, y, z));
		
		norm.normalize();
		
		// transform everything back to the world coordinate
		ray.intersection.point  = modelToWorld * Point3D(x, y, z);
		ray.intersection.normal = norm;
		ray.intersection.none = false;
		ray.intersection.t_value = t_1;
		
		return true;
	}
	double t = t_1 < t_2 ? t_1 : t_2;
	
	if (!ray.intersection.none && ray.intersection.t_value < t)
	{
		return false;
	}
	
	double x = tf_ray.origin[0] + t * tf_ray.dir[0];
	double y = tf_ray.origin[1] + t * tf_ray.dir[1];
	double z = tf_ray.origin[2] + t * tf_ray.dir[2];

	Vector3D norm = transNorm(worldToModel, Vector3D(x, y, z));

	norm.normalize();

	// transform everything back to the world coordinate
	ray.intersection.point  = modelToWorld * Point3D(x, y, z);
	ray.intersection.normal = norm;
	ray.intersection.none = false;
	ray.intersection.t_value = t;

	return true;
}

