#include "D3DEffect.h"
#include "CommonUtil.h"
#include <stdio.h>
#include <assert.h>

#pragma comment(lib,"d3dx9.lib")

D3DEffect::D3DEffect():
m_pEffect(NULL),
m_hPostProcess(NULL)
{
	for (int i = 0; i < NUMTEXTURE;i++)
	{
		m_hTextureSrc[i] = NULL;
	}
}

D3DEffect::~D3DEffect()
{
	Clear();
}

bool D3DEffect::LoadFromFile(LPDIRECT3DDEVICE9 pd3dDevice, const char *pShaderFile)
{
	if (!pShaderFile)
	{
		MessageBox(0, 0, "LoadFromFile: pShaderFile is NULL", 0);
	}

	HRESULT hr;
	DWORD dwShaderFlags = 0;
	LPD3DXBUFFER ppCompilationErrors = NULL;
	hr = D3DXCreateEffectFromFile(pd3dDevice, pShaderFile, 0, 0, dwShaderFlags, 0, &m_pEffect, &ppCompilationErrors);

	if (ppCompilationErrors)
	{
		char tmp[1024];
		sprintf(tmp, "compile error:%s", (char*)ppCompilationErrors->GetBufferPointer());
		MessageBox(0, 0, tmp, 0);
		SAFE_RELEASE(ppCompilationErrors);
		return false;
	}

	if (FAILED(hr))
	{
		MessageBox(0, 0, "LoadFromFile: D3DXCreateEffectFromFile() - FAILED", 0);
		return false;
	}

	m_hPostProcess = m_pEffect->GetTechniqueByName("vpProcess");
	for (int i = 0; i < NUMTEXTURE; i++) {
		char szName[256];
		sprintf(szName, "Texture%d", i);
		m_hTextureSrc[i] = m_pEffect->GetParameterByName(NULL, szName);
	}

	if (!m_hTextureSrc[0] || !m_hPostProcess)
	{
		return false;
	}

	return true;
}

void D3DEffect::Clear()
{
	SAFE_RELEASE(m_pEffect);
	m_hPostProcess = NULL;
	for (int i = 0; i < NUMTEXTURE; i++)
	{
		m_hTextureSrc[i] = NULL;
	}
}

bool D3DEffect::SetTechnique(const char *name)
{
	assert(m_pEffect);
	if (!name)
	{
		return false;
	}
	return SUCCEEDED(m_pEffect->SetTechnique(name));
}

bool D3DEffect::SetTexture(int index, LPDIRECT3DTEXTURE9 pTexture)
{
	assert(m_pEffect);
	if (index < 0 || index >= NUMTEXTURE || !pTexture)
	{
		return false;
	}
	return SUCCEEDED(m_pEffect->SetTexture(m_hTextureSrc[index], pTexture));
}

bool D3DEffect::SetFloat(const char *name, float value)
{
	assert(m_pEffect);
	D3DXHANDLE hHandle = m_pEffect->GetParameterByName(NULL, name);
	if (!hHandle)
	{
		return false;
	}

	FLOAT fValue = value;
	m_pEffect->SetFloat(hHandle, fValue);

	return true;
}

bool D3DEffect::SetInt(const char *name, int value)
{
	assert(m_pEffect);

	D3DXHANDLE hHandle = m_pEffect->GetParameterByName(NULL, name);
	if (!hHandle)
	{
		return false;
	}

	m_pEffect->SetInt(hHandle, value);

	return true;
}

bool D3DEffect::SetString(const char *name, const char* str)
{
	assert(m_pEffect);
	D3DXHANDLE hHandle = m_pEffect->GetParameterByName(NULL, name);
	if (!hHandle)
	{
		return false;
	}
	m_pEffect->SetString(hHandle, str);
	return true;
}
bool D3DEffect::SetVector(const char *name, float *value)
{
	assert(m_pEffect);

	D3DXHANDLE hHandle = m_pEffect->GetParameterByName(NULL, name);
	if (!hHandle)
	{
		return false;
	}

	D3DXVECTOR4 fValue = D3DXVECTOR4(value[0], value[1], value[2], value[3]);
	m_pEffect->SetVector(hHandle, &fValue);

	return true;
}
bool D3DEffect::SetMatrix(const char *name, float *value)
{
	assert(m_pEffect);

	D3DXHANDLE hHandle = m_pEffect->GetParameterByName(NULL, name);
	if (!hHandle)
	{
		return false;
	}

	D3DXMATRIX fValue = D3DXMATRIX(value);
	m_pEffect->SetMatrix(hHandle, &fValue);

	return true;
}

bool D3DEffect::Begin(UINT& cPasses)
{
	assert(m_pEffect);
	return SUCCEEDED(m_pEffect->Begin(&cPasses, 0));
}

bool D3DEffect::BeginPass(UINT pass)
{
	assert(m_pEffect);
	return SUCCEEDED(m_pEffect->BeginPass(pass));
}

void D3DEffect::EndPass()
{
	assert(m_pEffect);
	m_pEffect->EndPass();
}
void D3DEffect::End()
{
	assert(m_pEffect);
	m_pEffect->End();
}