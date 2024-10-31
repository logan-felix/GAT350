#pragma once
#include "Color.h"
#include "Ray.h"

class Material
{
public:
	Material() = default;
	Material(const color3_t& albedo) : m_albedo{ albedo } {}

	virtual bool Scatter(const ray_t& ray, const raycastHit_t& raycastHit, color3_t& attenuation, ray_t& scatter) const = 0;

	color3_t& GetColor() { return m_albedo; }
	virtual color3_t GetEmissive() const { return m_albedo; }

protected:
	color3_t m_albedo;
};

class Lambertian : public Material
{
public:
	Lambertian(const color3_t& albedo) : Material{ albedo } {}

	bool Scatter(const ray_t& ray, const raycastHit_t& raycastHit, color3_t& attenuation, ray_t& scatter) const override;
};

class Metal : public Material
{
public:
	Metal(const glm::vec3& albedo, float fuzz) : Material{ albedo }, m_fuzz{ fuzz } {}

	bool Scatter(const ray_t& ray, const raycastHit_t& raycastHit, color3_t& attenuation, ray_t& scatter) const override;

protected:
	float m_fuzz = 0;
};

class Emissive : public Material
{
public:
	Emissive(const color3_t& albedo, float intensity = 1) : Material{ albedo }, m_intensity{ intensity } {}

	bool Scatter(const ray_t& ray, const raycastHit_t& raycastHit, color3_t& color, ray_t& scattered) const override { return false; }
	color3_t GetEmissive() const override { return m_albedo * m_intensity; }

private:
	float m_intensity{ 1 };
};

class Dielectric : public Material
{
public:
	Dielectric(const glm::vec3& albedo, float refractiveIndex) : Material{ albedo }, m_refractiveIndex{ refractiveIndex } {}

	bool Scatter(const ray_t& ray, const raycastHit_t& raycastHit, color3_t& attenuation, ray_t& scatter) const override;

protected:
	float m_refractiveIndex = 0;
};