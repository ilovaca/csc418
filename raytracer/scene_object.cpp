/***********************************************************
     Starter code for Assignment 3

     This code was originally written by Jack Wang for
		    CSC418, SPRING 2005

		implements scene_object.h

***********************************************************/

#include <cmath>

#include <vector>
#include <algorithm>

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
	if (t <= 0)
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

// bool UnitSphere::intersect( Ray3D& ray, const Matrix4x4& worldToModel,
// 		const Matrix4x4& modelToWorld ) {
// 	// TODO: implement intersection code for UnitSphere, which is centred 
// 	// on the origin.  
// 	//
// 	// Your goal here is to fill ray.intersection with correct values
// 	// should an intersection occur.  This includes intersection.point, 
// 	// intersection.normal, intersection.none, intersection.t_value.   
// 	//
// 	// HINT: Remember to first transform the ray into object space  
// 	// to simplify the intersection test.
	
// 	// again, transform the ray into object space
// 	Ray3D tf_ray (worldToModel * ray.origin, worldToModel * ray.dir);
// 	// Since the equation of a unit sphere is given by 
// 	// x ^ 2 + y ^ 2 + z ^ 2 = 1
// 	// which therefore implies that we need to solve for the quadratic equation
// 	// (tf_ray.origin[0] + t * tf_ray.dir[0]) ^ 2 + 
// 	// (tf_ray.origin[1] + t * tf_ray.dir[1]) ^ 2 + 
// 	// (tf_ray.origin[2] + t * tf_ray.dir[2]) ^ 2 = 1
// 	// After simplification, we get
// 	double A = 
// 		tf_ray.dir[0] * tf_ray.dir[0] + 
// 		tf_ray.dir[1] * tf_ray.dir[1] + 
// 		tf_ray.dir[2] * tf_ray.dir[2];
// 	double B = 
// 		2 * tf_ray.origin[0] * tf_ray.dir[0] + 
// 		2 * tf_ray.origin[1] * tf_ray.dir[1] + 
// 		2 * tf_ray.origin[2] * tf_ray.dir[2];
// 	double C = 
// 		tf_ray.origin[0] * tf_ray.origin[0] + 
// 		tf_ray.origin[1] * tf_ray.origin[1] + 
// 		tf_ray.origin[2] * tf_ray.origin[2] - 1;
	
// 	double det = B * B - 4 * A * C;
	
// 	if (det < 0)
// 	{
// 		return false;
// 	}
// 	double t_1 = (- B - std::sqrt(det)) / (2 * A);
// 	double t_2 = (- B + std::sqrt(det)) / (2 * A);
	
// 	if (t_1 <= 0 && t_2 <= 0)
// 	{
// 		return false;
// 	}
// 	if (t_1 <= 0)
// 	{
// 		if (!ray.intersection.none && ray.intersection.t_value < t_2)
// 		{
// 			return false;
// 		}
		
// 		double x = tf_ray.origin[0] + t_2 * tf_ray.dir[0];
// 		double y = tf_ray.origin[1] + t_2 * tf_ray.dir[1];
// 		double z = tf_ray.origin[2] + t_2 * tf_ray.dir[2];
		
// 		Vector3D norm = transNorm(worldToModel, Vector3D(x, y, z));
		
// 		norm.normalize();
		
// 		// transform everything back to the world coordinate
// 		ray.intersection.point  = modelToWorld * Point3D(x, y, z);
// 		ray.intersection.normal = norm;
// 		ray.intersection.none = false;
// 		ray.intersection.t_value = t_2;
		
// 		return true;
// 	}
// 	if (t_2 <= 0)
// 	{
// 		if (!ray.intersection.none && ray.intersection.t_value < t_1)
// 		{
// 			return false;
// 		}
		
// 		double x = tf_ray.origin[0] + t_1 * tf_ray.dir[0];
// 		double y = tf_ray.origin[1] + t_1 * tf_ray.dir[1];
// 		double z = tf_ray.origin[2] + t_1 * tf_ray.dir[2];
		
// 		Vector3D norm = transNorm(worldToModel, Vector3D(x, y, z));
		
// 		norm.normalize();
		
// 		// transform everything back to the world coordinate
// 		ray.intersection.point  = modelToWorld * Point3D(x, y, z);
// 		ray.intersection.normal = norm;
// 		ray.intersection.none = false;
// 		ray.intersection.t_value = t_1;
		
// 		return true;
// 	}
// 	double t = t_1 < t_2 ? t_1 : t_2;
	
// 	if (!ray.intersection.none && ray.intersection.t_value < t)
// 	{
// 		return false;
// 	}
	
// 	double x = tf_ray.origin[0] + t * tf_ray.dir[0];
// 	double y = tf_ray.origin[1] + t * tf_ray.dir[1];
// 	double z = tf_ray.origin[2] + t * tf_ray.dir[2];

// 	Vector3D norm = transNorm(worldToModel, Vector3D(x, y, z));

// 	norm.normalize();

// 	// transform everything back to the world coordinate
// 	ray.intersection.point  = modelToWorld * Point3D(x, y, z);
// 	ray.intersection.normal = norm;
// 	ray.intersection.none = false;
// 	ray.intersection.t_value = t;

// 	return true;
// }
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
	
	Ray3D tf_ray (worldToModel * ray.origin, worldToModel * ray.dir);

	Point3D origin(0,0,0);

	Vector3D dist = tf_ray.origin - origin;
	

	double t = -1, t2;

	double A = tf_ray.dir.dot(tf_ray.dir);
	double B = dist.dot(tf_ray.dir);
	double C = dist.dot(dist) - 1;
	double det = B * B - A * C;


	if (det == 0) {
		t = -B/A;
	} else if (det > 0) {
		t = (-B + sqrt(det)) / A;
		t2 = (-B - sqrt(det)) / A;
		t = t < t2 ? t : t2;
	} else {
		return false;
	}

	// backwards
	if (t <= 0) return false;

	if (ray.intersection.none || t < ray.intersection.t_value) {

		Point3D intersect = tf_ray.origin + t * tf_ray.dir;
		Vector3D n = 2 * (intersect - origin);
		n.normalize();

		ray.intersection.t_value = t;
		ray.intersection.point = modelToWorld * intersect;
		ray.intersection.normal = transNorm(worldToModel, n);
		ray.intersection.normal.normalize();
		ray.intersection.none = false;
		return true;
	}

	return false;
}

bool UnitCylinder::intersect( Ray3D& ray, const Matrix4x4& worldToModel, 
		const Matrix4x4& modelToWorld)
{
	// Here we define the UnitCylinder as a cylinder of radius 1, length 1
	// with its upper plane given by z = 1 and lower plane given by z = 0.
	
	// again, transform the ray into object space
	Ray3D tf_ray (worldToModel * ray.origin, worldToModel * ray.dir);
	
	// Dynamically store the values of t that satisfies the intersection requirements.
	std::vector < double > t_values;
	
	// First, naively assume that the cylinder is infinitely long.
	// In this case, we are going to solve for the quadratic equation
	// (tf_ray.origin[0] + t * tf_ray.dir[0]) ^ 2 + 
	// (tf_ray.origin[1] + t * tf_ray.dir[1]) ^ 2 = 1
	double A = 
		tf_ray.dir[0] * tf_ray.dir[0] + 
		tf_ray.dir[1] * tf_ray.dir[1];
	double B = 
		2 * tf_ray.origin[0] * tf_ray.dir[0] +
		2 * tf_ray.origin[1] * tf_ray.dir[1];
	double C = 
		tf_ray.origin[0] * tf_ray.origin[0] + 
		tf_ray.origin[1] * tf_ray.origin[1] - 1;
	
	double det = B * B - 4 * A * C;
	
	if (det >= 0)
	{
		double t_1 = (- B - std::sqrt(det)) / (2 * A);
		double t_2 = (- B - std::sqrt(det)) / (2 * A);
		
		// Second, impose the constraint that points of intersections are within the finite unit length.
		double z_1 = tf_ray.origin[2] + t_1 * tf_ray.dir[2];
		double z_2 = tf_ray.origin[2] + t_2 * tf_ray.dir[2];
		
		if (t_1 > 0 && z_1 >= 0 && z_1 <= 1)
		{
			t_values.push_back(t_1);
		}
		if (t_2 > 0 && z_2 >= 0 && z_2 <= 1)
		{
			t_values.push_back(t_2);
		}
	}
	
	// Third, check the upper and the lower unit circle.
	double t_1 = (1 - tf_ray.origin[2]) / tf_ray.dir[2];
	double t_2 = (0 - tf_ray.origin[2]) / tf_ray.dir[2];
	
	double d_1 = 
		(tf_ray.origin[0] + t_1 * tf_ray.dir[0]) * (tf_ray.origin[0] + t_1 * tf_ray.dir[0]) + 
		(tf_ray.origin[1] + t_1 * tf_ray.dir[1]) * (tf_ray.origin[1] + t_1 * tf_ray.dir[1]);
	double d_2 = 
		(tf_ray.origin[0] + t_2 * tf_ray.dir[0]) * (tf_ray.origin[0] + t_2 * tf_ray.dir[0]) + 
		(tf_ray.origin[1] + t_2 * tf_ray.dir[1]) * (tf_ray.origin[1] + t_2 * tf_ray.dir[1]);
	
	if (t_1 > 0 && d_1 <= 1)
	{
		t_values.push_back(t_1);
	}
	if (t_2 > 0 && d_2 <= 1)
	{
		t_values.push_back(t_2);
	}
	
	if (t_values.size() == 0)
	{
		return false;
	}
	
	double t = *std::min_element(t_values.begin(), t_values.end());
	
	if (!ray.intersection.none && ray.intersection.t_value < t)
	{
		return false;
	}
	
	double x = tf_ray.origin[0] + t * tf_ray.dir[0];
	double y = tf_ray.origin[1] + t * tf_ray.dir[1];
	double z = tf_ray.origin[2] + t * tf_ray.dir[2];

	Vector3D norm;
	
	if (z == 0)
		norm = transNorm(worldToModel, Vector3D(0, 0, -1));
	else if (z == 1)
		norm = transNorm(worldToModel, Vector3D(0, 0, 1));
	else
		norm = transNorm(worldToModel, Vector3D(x, y, 0));

	norm.normalize();

	// transform everything back to the world coordinate
	ray.intersection.point  = modelToWorld * Point3D(x, y, z);
	ray.intersection.normal = norm;
	ray.intersection.none = false;
	ray.intersection.t_value = t;

	return true;
}