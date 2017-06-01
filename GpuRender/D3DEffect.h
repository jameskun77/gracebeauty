#ifndef     __D3DEFFECT__H_
#define     __D3DEFFECT__H_ 

#include <d3dx9.h>

#define NUMTEXTURE 1

class D3DEffect
{
public:
	D3DEffect();
	~D3DEffect();

	bool LoadFromFile(LPDIRECT3DDEVICE9 pd3dDevice, const char *pShaderFile);
	bool LoadFromStr(LPDIRECT3DDEVICE9 pd3dDevice, const char *strHlsl);

	bool SetTechnique(const char *name);
	bool SetTexture(int index, LPDIRECT3DTEXTURE9 pTexture);
	bool SetFloat(const char *name, float value);
	bool SetInt(const char *name, int value);
	bool SetString(const char *name, const char* str);
	bool SetVector(const char *name, float *value);
	bool SetMatrix(const char *name, float *value);

	bool Begin(UINT& cPasses);
	bool BeginPass(UINT pass);
	void EndPass();
	void End();
	void Clear();

protected:
	LPD3DXEFFECT m_pEffect;
	D3DXHANDLE	 m_hPostProcess;
	D3DXHANDLE   m_hTextureSrc[NUMTEXTURE];
};


#endif
