#ifndef __D3D_RENDER_H__
#define __D3D_RENDER_H__

#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include "CommonUtil.h"
#include "D3DEffect.h"

#define TEMP_TEXTURE_NUM 1

class D3DVideoRender
{
public:
	D3DVideoRender();
	virtual ~D3DVideoRender();

	bool Init(HWND hWnd, int nWidth, int nHeight);
	void Clear();
	bool RenderToTexture(LPBYTE src, LPBYTE dst, int w, int h, int wstride);
	bool DrawToWindow(LPBYTE src, int w, int h, int wstride);

protected:
	void DrawPass();
	bool CopyToTexture(LPBYTE rgb, LPDIRECT3DTEXTURE9 pTexture, int w, int h, int wstride);
	bool CopyToMemory(LPBYTE dst, int w, int h, int wstride);
	bool SetTextureRenderTarget(int index);

	bool CreateD3D(HWND hWnd, int nWidth, int nHeight);
	void Destory();

	bool CreateTexture(int width, int height, LPDIRECT3DTEXTURE9* pTexture, DWORD Usage, D3DPOOL Pool);

protected:
	HWND                    m_hWnd;
	int                     m_nWidth;
	int                     m_nHeight;

	LPDIRECT3D9             m_pDev;
	LPDIRECT3DDEVICE9       m_pd3dDevice;
	LPDIRECT3DTEXTURE9      m_pSrcVideoTexture;
	LPDIRECT3DTEXTURE9      m_pMemoryTexture;

	LPDIRECT3DTEXTURE9      m_pTempTexture[TEMP_TEXTURE_NUM]; // render to texture
	LPDIRECT3DSURFACE9		m_pTempSurface[TEMP_TEXTURE_NUM];

	LPDIRECT3DVERTEXBUFFER9 m_pd3dVertexBuffer;
	D3DFORMAT               m_format;
	D3DEffect				m_effect;

};

#endif