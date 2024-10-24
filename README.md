# Raytracer Project

## Overview
This project implements a simple raytracer capable of rendering scenes composed of spheres and planes with lighting effects. The raytracer calculates the color of pixels based on light interactions with objects in a 3D scene.

## Features
- **Ray Casting**: Rays are cast from a viewpoint into the scene, determining the color of pixels based on object intersections.
- **Lighting**: Supports ambient and point lighting with diffuse and specular reflection calculations.
- **Reflections**: Implements reflections up to a specified limit to enhance realism.
- **User-defined Scene**: Scenes can be defined through a source file containing object and light properties.

## Requirements
- C++ Compiler (e.g., g++, clang++)
- Basic libraries such as `<cmath>` and `<fstream>`

## File Structure
- **dataStructures.h**: Contains class and struct definitions for objects, vectors, colors, and lights.
- **Utilities.h**: Declares global constants, variables, and function prototypes.
- **Utilities.cpp**: Implements utility functions and manages global variables.
- **trig.h**: Provides mathematical functions for vector operations.
- **trig.cpp**: Implements mathematical functions for operations such as dot product, cross product, normalization, and quadratic solutions.
- **lighting.cpp**: Handles lighting calculations.
- **raytracer.cpp**: Implements the ray tracing logic.
- **fileio.cpp**: Handles file input for scene definition.
