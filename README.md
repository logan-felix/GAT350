# 3D Rendering Projects
This repository showcases two key projects in 3D graphics rendering: a **Software Renderer** and a **Ray Tracer**. Both projects demonstrate advanced rendering techniques, highlighting the power and versatility of computer graphics.  
## Purpose
The repository serves as a resource for learning and experimenting with rendering techniques such as shader implementation, lighting models, and material handling. It is ideal for enthusiasts, students, and developers interested in understanding low-level rendering pipelines and ray tracing algorithms.

---

## Included Projects
### 1. Software Renderer
A rasterization-based renderer that supports real-time rendering of 3D models and primitives. It emphasizes shader support and lighting models.
**Key Features:**
- **Shader Support**: Implements both vertex and fragment shaders, enabling flexible transformations and lighting effects.
- **Lighting Models**:
  - **Gouraud Shading**: Smooth per-vertex lighting.
  - **Phong Shading**: Realistic per-fragment lighting.
- **Libraries Used**: 
  - SDL for windowing and event handling.
  - GLM for mathematical operations.
- **Post-Processing**: Additional effects for enhanced rendering output.
- **Primitive Rendering**: Efficient rendering of basic geometric shapes.
---
### 2. Ray Tracer
A physics-based renderer that simulates the behavior of light for highly realistic image synthesis.
**Key Features:**
- **Material Support**:
  - Lambertian (diffuse).
  - Metallic (reflective).
  - Dielectric (refractive).
- **Anti-Aliasing**: Reduces visual artifacts for smoother images.
- **Multiple Bounce Reflections**: Simulates complex light interactions for enhanced realism.
- **Primitives and Models**: Renders simple shapes and complex 3D models with accurate shading.
---
## Building the Projects
Both projects require the following dependencies:
- **SDL2**: For window creation and input handling.
- **GLM**: For vector and matrix mathematics.
## Technical Details
### Software Renderer
#### Shader Support
The software renderer supports two shader stages:
- **Vertex Shader**: Handles geometric transformations such as scaling, rotation, and projection for vertices.
- **Fragment Shader**: Calculates per-pixel lighting, colors, and effects, ensuring detailed output.
#### Lighting Techniques
- **Gouraud Shading**: Computes lighting at the vertices and interpolates the results across surfaces. This technique is computationally efficient but less detailed.
- **Phong Shading**: Calculates lighting per fragment (pixel), offering more precise and visually realistic lighting at the cost of higher computational demand.
---
### Ray Tracer
#### Material Types
- **Lambertian (Diffuse)**: Represents surfaces that scatter light evenly in all directions.
- **Metallic (Reflective)**: Models reflective surfaces with adjustable roughness for realism.
- **Dielectric (Refractive)**: Simulates transparent materials like glass or water, considering refraction and Fresnel effects.
#### Anti-Aliasing
The ray tracer implements stochastic sampling, taking multiple samples per pixel and averaging the results to reduce jagged edges and improve image quality.
#### Multiple Bounce Reflections
Simulates realistic light behavior by allowing rays to bounce off surfaces multiple times, enabling complex interactions like refraction, reflection, and shadowing.
