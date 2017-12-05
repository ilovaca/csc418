/***********************************************************
     Starter code for Assignment 3

     This code was originally written by Jack Wang for
		    CSC418, SPRING 2005

		implements light_source.h

***********************************************************/

#include <algorithm>
#include <cassert>
#include <cmath>
#include <GL/glut.h>
#include "light_source.h"

extern int width;
extern int height;
extern GLubyte *textureImage;
extern Material _2D_Texture;

extern int env_width;
extern int env_height;
extern GLubyte *envImage_pisa;
extern Material EnvMapping;

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


	if (ray.intersection.mat == &_2D_Texture)
	{
		int x = width  * (std::atan2(ray.intersection.point_obj_space[0], ray.intersection.point_obj_space[2]) / (2 * M_PI) + 0.5);
		int y = height * (std::asin (ray.intersection.point_obj_space[1]) / M_PI + 0.5);

		float r = textureImage[y * 3 * width + x * 3 + 0] * 1.0 / 255;
		float g = textureImage[y * 3 * width + x * 3 + 1] * 1.0 / 255;
		float b = textureImage[y * 3 * width + x * 3 + 2] * 1.0 / 255;

		ray.col = ray.col + Colour(r, g, b);

		return; 
	}
	if (ray.intersection.mat == &EnvMapping)
	{
		auto normal = ray.intersection.normal;
                auto viewDir = -ray.dir;
		auto reflectDir = 2.0 * viewDir.dot(normal)*normal - viewDir;
		reflectDir.normalize();

		int x = env_width  * (std::atan2(reflectDir[0], reflectDir[2]) / (2 * M_PI) + 0.5);
		int y = env_height * (std::asin (reflectDir[1]) / M_PI + 0.5);

		float r = envImage_pisa[y * 3 * env_width + x * 3 + 0] * 1.0 / 255;
		float g = envImage_pisa[y * 3 * env_width + x * 3 + 1] * 1.0 / 255;
		float b = envImage_pisa[y * 3 * env_width + x * 3 + 2] * 1.0 / 255;

		ray.col = ray.col + Colour(r, g, b);

		return;
	}

	// light direction
	auto lightDir = (_pos - point);
	lightDir.normalize();
	// normal at point
	auto normal = /*Vector3D(0, 0, 1);*/ ray.intersection.normal;
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
	ray.col = ray.col + finalColor;
}

