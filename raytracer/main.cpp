/***********************************************************
Starter code for Assignment 3

This code was originally written by Jack Wang for
CSC418, SPRING 2005

***********************************************************/


#include "raytracer.h"
#include "texture.h"
#include <cstdlib>

Material _2D_Texture (Colour(0.3, 0.3, 0.3), Colour(0.75164, 0.60648, 0.22648),
		Colour(0.628281, 0.555802, 0.366065),
		51.2);

Material EnvMapping (Colour(0.3, 0.3, 0.3), Colour(0.75164, 0.60648, 0.22648),
                Colour(0.628281, 0.555802, 0.366065),
                51.2);

int main(int argc, char* argv[])
{
	// Build your scene and setup your camera here, by calling 
	// functions from Raytracer.  The code here sets up an example
	// scene and renders it from two different view points, DO NOT
	// change this if you're just implementing part one of the 
	// assignment.  
	Raytracer raytracer;
	int width = 320;
	int height = 240;

	if (argc == 3) {
		width = atoi(argv[1]);
		height = atoi(argv[2]);
	}
	
	// Initialize texture.
	texture_init();

	// Camera parameters.
	Point3D eye(0, 0, 1);
	Vector3D view(0, 0, -1);
	Vector3D up(0, 1, 0);
	double fov = 60;

	// Defines a material for shading.
	_2D_Texture.reflection_coeff = 0.4;
	EnvMapping.reflection_coeff = 0.4;

	Material gold(Colour(0.3, 0.3, 0.3), Colour(0.75164, 0.60648, 0.22648),
		Colour(0.628281, 0.555802, 0.366065),
		51.2);
	gold.reflection_coeff = 0.4;	

	Material jade(Colour(0, 0, 0), Colour(0.54, 0.89, 0.63),
		Colour(0.316228, 0.316228, 0.316228),
		12.8);
	jade.reflection_coeff = 0.3;
	// Defines a point light source.
	raytracer.addLightSource(new PointLight(Point3D(0, 0, 5),
		Colour(0.9, 0.9, 0.9)));
	// raytracer.addLightSource(new AreaLight(Point3D(0,0,50),
	// 	1.0, Vector3D(0,0,-1), Colour(1.0, 1.0, 0.5)));
	// Add a unit square into the scene with material mat.
	SceneDagNode* sphere = raytracer.addObject(new UnitSphere(), &EnvMapping);
	SceneDagNode* plane = raytracer.addObject(new UnitSquare(), &jade);
	SceneDagNode* cylinder = raytracer.addObject(new UnitCylinder(), &gold);

	// Apply some transformations to the unit square.
	double factor1[3] = { 1.0, 1.0, 1.0 };
	double factor2[3] = { 6.0, 6.0, 6.0 };
	double factor3[3] = { 0.5, 0.5, 0.5 };
	raytracer.translate(sphere, Vector3D(0, 0, -5));
	raytracer.rotate(sphere, 'x', -45);
	raytracer.rotate(sphere, 'z', 45);
	raytracer.scale(sphere, Point3D(0, 0, 0), factor1);

	raytracer.translate(plane, Vector3D(0, 0, -7));
	raytracer.rotate(plane, 'z', 45);
	raytracer.scale(plane, Point3D(0, 0, 0), factor2);

	raytracer.translate(cylinder, Vector3D(-1, -1, -4));
	raytracer.rotate(cylinder, 'x', 60);
	raytracer.rotate(cylinder, 'y', 90);
	raytracer.scale(cylinder, Point3D(0, 0, 0), factor3);
	
	// Render the scene, feel free to make the image smaller for
	// testing purposes.	
	raytracer.render(width, height, eye, view, up, fov, "view1.bmp");

	// Render it from a different point of view.
	Point3D eye2(4, 2, 1);
	Vector3D view2(-4, -2, -6);
	raytracer.render(width, height, eye2, view2, up, fov, "view2.bmp");

	return 0;
}
