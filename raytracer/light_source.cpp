/***********************************************************
     Starter code for Assignment 3

     This code was originally written by Jack Wang for
		    CSC418, SPRING 2005

		implements light_source.h

***********************************************************/

#include <algorithm>
#include <cassert>
#include <cmath>
#include "light_source.h"

void PointLight::shade( Ray3D& ray ) {
	// TODO: implement this function to fill in values for ray.col 
	// using phong shading.  Make sure your vectors are normalized, and
	// clamp colour values to 1.0.
	//
	// It is assumed at this point that the intersection information in ray 
	// is available.  So be sure that traverseScene() is called on the ray 
	// before this function.  

	// point of intersection
	auto point = ray.intersection.point;
	// point material
	auto material = *(ray.intersection.mat);
	// light direction
	auto lightDir = (_pos - point);
	lightDir.normalize();
	// normal at point
	auto normal = ray.intersection.normal;
	// diffuse component. FIXME
	auto diffuseLight = std::max(normal.dot(lightDir), 0.0);
	auto diffuseComponent =  material. diffuse * Colour(diffuseLight, diffuseLight, diffuseLight);
	// specular direction
	auto specularDir = (2.0 * lightDir.dot(normal)*normal - lightDir);
	specularDir.normalize();
	// view dir, is the opposite of ray dir
	auto viewDir = -ray.dir;
	// assert(viewDir.length() == 1);
	// specular component
	auto specularLight = std::pow(std::max(specularDir.dot(viewDir), 0.0), material.specular_exp);
	auto specularComponent = material.specular * Colour(specularLight, specularLight, specularLight);
	// final color, should be added to existing color of the ray
	auto finalColor = (material.ambient + diffuseComponent + specularComponent);
	finalColor.clamp();
	ray.col = ray.col + material.ambient;
}

