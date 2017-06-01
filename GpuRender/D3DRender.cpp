#include "D3DRender.h"
#include <assert.h>

#pragma comment(lib,"d3d9.lib")

struct CUSTOMVERTEX
{
	FLOAT x, y, z, rhw;
	FLOAT u, v;
};
#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZRHW |D3DFVF_TEX1)


D3DVideoRender::D3DVideoRender() :
m_hWnd(NULL),
m_nWidth(0),
m_nHeight(0),
m_pDev(NULL),
m_pd3dDevice(NULL),
m_pSrcVideoTexture(NULL),
m_pMemoryTexture(NULL),
m_pd3dVertexBuffer(NULL)
{
	for (int i = 0; i < TEMP_TEXTURE_NUM; i++)
	{
		m_pTempTexture[i] = NULL;
		m_pTempSurface[i] = NULL;
	}
}

D3DVideoRender::~D3DVideoRender()
{
	Destory();
}

bool D3DVideoRender::Init(HWND hWnd, int nWidth, int nHeight)
{
	if (nWidth <= 0 || nHeight <= 0)
	{
		MessageBox(0, 0, "width and height is illegal!", 0);
		return false;
	}

	Destory();

	m_hWnd = (IsWindow(hWnd) ? hWnd : GetDesktopWindow());
	m_nWidth = nWidth;
	m_nHeight = nHeight;

	__try
	{
		if (CreateD3D(m_hWnd, m_nWidth, m_nHeight))
		{
			return true;
		}

	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		return false;
	}


	MessageBox(0, 0, "initialize D3D failed !", 0);
	return false;
}

void D3DVideoRender::Clear()
{
	Destory();
}

bool D3DVideoRender::CreateD3D(HWND hWnd, int nWidth, int nHeight)
{
	m_pDev = Direct3DCreate9(D3D_SDK_VERSION);
	if (m_pDev == NULL)
	{
		MessageBox(0, 0, "Direct3DCreate9 failed !", 0);
		return false;
	}

	D3DCAPS9 caps;
	HRESULT hr = m_pDev->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &caps);
	if (FAILED(hr))
	{
		Destory();
		MessageBox(0, 0, "GetDeviceCaps failed !", 0);
		return false;
	}

	if (!(caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT) ||
		caps.PixelShaderVersion < D3DPS_VERSION(3, 0))
	{
		Destory();
		MessageBox(0, 0, "caps.DevCaps failed", 0);
		return false;
	}

	int vp = D3DCREATE_HARDWARE_VERTEXPROCESSING;
	m_format = D3DFMT_A8R8G8B8;

	D3DPRESENT_PARAMETERS d3dpp;
	memset(&d3dpp, 0, sizeof(D3DPRESENT_PARAMETERS));
	d3dpp.BackBufferWidth = nWidth;
	d3dpp.BackBufferHeight = nHeight;
	d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;
	d3dpp.BackBufferCount = 1;
	d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;
	d3dpp.MultiSampleQuality = 0;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.hDeviceWindow = hWnd;
	d3dpp.Windowed = TRUE;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24X8;

	hr = m_pDev->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		vp,
		&d3dpp,
		&m_pd3dDevice);

	//const TCHAR* ptchar = DXGetErrorDescription(hr);
	//const WCHAR* pchar = DXGetErrorString(hr);

	if (FAILED(hr))
	{
		MessageBox(0, 0, "m_pDev->CreateDevice failed", 0);
		memset(&d3dpp, 0, sizeof(D3DPRESENT_PARAMETERS));

		d3dpp.BackBufferWidth = nWidth;
		d3dpp.BackBufferHeight = nHeight;
		d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
		d3dpp.BackBufferCount = 1;
		d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;
		d3dpp.MultiSampleQuality = 0;
		d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
		d3dpp.hDeviceWindow = hWnd;
		d3dpp.Windowed = TRUE;
		d3dpp.EnableAutoDepthStencil = TRUE;
		d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
		m_format = D3DFMT_X8R8G8B8;

		hr = m_pDev->CreateDevice(
			D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			vp,
			&d3dpp,
			&m_pd3dDevice);
		if (FAILED(hr))
		{
			Destory();
			MessageBox(0, 0, "m_pDev->CreateDevice failed", 0);
			return false;
		}
	}

	m_pd3dDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
	m_pd3dDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	m_pd3dDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	m_pd3dDevice->SetRenderState(D3DRS_DITHERENABLE, FALSE);
	m_pd3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);


	CUSTOMVERTEX* pVertices = NULL;
	CUSTOMVERTEX vertices[] =
	{

		{ 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f },
		{ 0.0f, nHeight, 0.0f, 1.0f, 0.0f, 1.0f },
		{ nWidth, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f },
		{ nWidth, nHeight, 0.0f, 1.0f, 1.0f, 1.0f },

	};

	if (FAILED(m_pd3dDevice->CreateVertexBuffer(4 * sizeof(CUSTOMVERTEX),
		0, D3DFVF_CUSTOMVERTEX,
		D3DPOOL_DEFAULT, &m_pd3dVertexBuffer, NULL)))
	{
		Destory();
		MessageBox(0, 0, "m_pd3dDevice->CreateVertexBuffer failed", 0);
		return false;
	}

	hr = m_pd3dVertexBuffer->Lock(0, sizeof(vertices), (void**)&pVertices, 0);
	if (SUCCEEDED(hr))
	{
		memcpy(pVertices, vertices, sizeof(vertices));
		m_pd3dVertexBuffer->Unlock();
	}

	if (!m_effect.LoadFromFile(m_pd3dDevice, "posteffect.txt"))
	{
		Destory();
		return false;
	}

	return true;
}

void D3DVideoRender::Destory()
{
	m_effect.Clear();
	SAFE_RELEASE(m_pDev);
	SAFE_RELEASE(m_pd3dDevice);
	SAFE_RELEASE(m_pd3dVertexBuffer);
	SAFE_RELEASE(m_pSrcVideoTexture);
}

bool D3DVideoRender::SetTextureRenderTarget(int index)
{
	if (index >= 0 || index <= TEMP_TEXTURE_NUM - 1)
	{
		return (SUCCEEDED(m_pTempTexture[index]->GetSurfaceLevel(0, &m_pTempSurface[index])) &&
			SUCCEEDED(m_pd3dDevice->SetRenderTarget(0, m_pTempSurface[index])));
	}

	return false;
}

bool D3DVideoRender::CopyToTexture(LPBYTE rgb, LPDIRECT3DTEXTURE9 pTexture, int w, int h, int wstride)
{
	D3DLOCKED_RECT rcLock;
	HRESULT hr = pTexture->LockRect(0, &rcLock, 0, 0);
	if (FAILED(hr)) {
		MessageBox(0, 0, "CopyToTexture LockRect failed", 0);
		return false;
	}

	if ((w << 2) == wstride  && wstride == rcLock.Pitch) {
		memcpy(rcLock.pBits, rgb, wstride * h);
		int err = GetLastError();
	}
	else{
		unsigned char *pdst = (unsigned char*)rcLock.pBits + (h - 1)*rcLock.Pitch;
		for (int y = 0; y<h; y++) {
			memcpy(pdst, rgb, wstride);
			rgb += wstride;
			pdst -= rcLock.Pitch;
		}
	}
	return SUCCEEDED(pTexture->UnlockRect(0));
}

bool D3DVideoRender::CopyToMemory(LPBYTE dst, int w, int h, int wstride)
{
	HRESULT hr;
	if (!m_pMemoryTexture)
	{
		D3DSURFACE_DESC RenderDesc;
		if (FAILED(m_pTempSurface[TEMP_TEXTURE_NUM -1]->GetDesc(&RenderDesc)))
		{
			return false;
		}

		hr = m_pd3dDevice->CreateTexture(
			RenderDesc.Width,
			RenderDesc.Height,
			1,
			0,
			RenderDesc.Format,
			D3DPOOL_SYSTEMMEM, //这里一定要sys
			&m_pMemoryTexture,
			NULL);
		if (FAILED(hr))
		{
			return false;
		}
	}

	IDirect3DSurface9 *pMemSurface = NULL;
	hr = m_pMemoryTexture->GetSurfaceLevel(0, &pMemSurface);
	if (FAILED(hr))
	{
		SAFE_RELEASE(m_pMemoryTexture);
		return false;
	}
	hr = m_pd3dDevice->GetRenderTargetData(m_pTempSurface[TEMP_TEXTURE_NUM - 1], pMemSurface);
	if (FAILED(hr))
	{
		SAFE_RELEASE(m_pMemoryTexture);
		pMemSurface->Release();
		return false;
	}

	D3DLOCKED_RECT  rc;
	hr = pMemSurface->LockRect(&rc, 0, 0);
	if (FAILED(hr))
	{
		SAFE_RELEASE(m_pMemoryTexture);
		pMemSurface->Release();
		return false; 
	}

	LPBYTE psrc = (LPBYTE)rc.pBits;
	for (int i = 0; i < h; i++)
	{
		memcpy(dst, psrc, wstride);
		dst += wstride;
		psrc += rc.Pitch;
	}
	psrc = (LPBYTE)rc.pBits;
	pMemSurface->UnlockRect();
	pMemSurface->Release();
	return true;
}

bool D3DVideoRender::CreateTexture(int width, int height, LPDIRECT3DTEXTURE9* pTexture, DWORD Usage, D3DPOOL Pool)
{
	HRESULT hr = m_pd3dDevice->CreateTexture(
		width,
		height,
		1,
		Usage, //一般为0，为rendertarget，Pool设为D3DPOOL_DEFAULT
		m_format,
		Pool,  //一般为D3DPOOL_MANAGED
		pTexture,
		NULL);
	if (FAILED(hr))
	{
		MessageBox(0, 0, "CreateTexture failed", 0);
		return false;
	}

	return true;
}

void D3DVideoRender::DrawPass()
{
	m_pd3dDevice->SetStreamSource(0, m_pd3dVertexBuffer, 0, sizeof(CUSTOMVERTEX));
	m_pd3dDevice->SetFVF(D3DFVF_CUSTOMVERTEX);
	m_pd3dDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

bool D3DVideoRender::RenderToTexture(LPBYTE src, LPBYTE dst, int w, int h, int wstride)
{
	assert(m_pd3dDevice);
	
	if (!m_pSrcVideoTexture || w != m_nWidth || h != m_nHeight)
	{
		SAFE_RELEASE(m_pSrcVideoTexture);
		m_nWidth = w;
		m_nHeight = h;
		CreateTexture(m_nWidth, m_nHeight, &m_pSrcVideoTexture, 0, D3DPOOL_MANAGED);
	}

	if (!CopyToTexture(src, m_pSrcVideoTexture, w, h, wstride))
	{
		MessageBox(0, 0, "CopyToTexture failed", 0);
		return false;
	}

	float width = (float)m_nWidth;
	float height = (float)m_nHeight;

	IDirect3DSurface9 *pTmpSur = 0;
	HRESULT hr = m_pd3dDevice->GetRenderTarget(0, &pTmpSur);
	if (SUCCEEDED(hr))
	{
		D3DSURFACE_DESC desc;
		if (SUCCEEDED(pTmpSur->GetDesc(&desc)))
		{
			width = (float)desc.Width;
			height = (float)desc.Height;
		}
		pTmpSur->Release();
	}

	if (!m_pTempTexture[0] || w != m_nWidth || h != m_nHeight)
	{
		for (int i = 0; i < TEMP_TEXTURE_NUM; i++)
		{
			SAFE_RELEASE(m_pTempTexture[i]);
			if (!CreateTexture(m_nWidth, m_nHeight, &m_pTempTexture[i], D3DUSAGE_RENDERTARGET, D3DPOOL_DEFAULT))
			{
				return false;
			}
		}
	}

	m_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(123, 65, 255), 1.0f, 0);

	if (SUCCEEDED(m_pd3dDevice->BeginScene()))
	{
		if (!SetTextureRenderTarget(0))
		{
			MessageBox(0, 0, "SetTextureRenderTarget failed", 0);
			return false;
		}

		UINT cPasses = 0;
		bool result = false;
		result = m_effect.SetTechnique("vpProcess");
		result = m_effect.Begin(cPasses);

		result = m_effect.SetFloat("width", (float)m_nWidth);
		result = m_effect.SetFloat("height", (float)m_nHeight);
		result = m_effect.SetFloat("step", 1.0f);
		result = m_effect.SetFloat("radius", 10.0f);

		result = m_effect.SetTexture(0, m_pSrcVideoTexture);
		result = m_effect.BeginPass(0);

		DrawPass();

		m_effect.EndPass();
		m_effect.End();

		m_pd3dDevice->EndScene();
	}

	bool bok = CopyToMemory(dst, (int)w, (int)h, wstride);

	if (m_pTempSurface[TEMP_TEXTURE_NUM - 1])
	{
		m_pTempSurface[TEMP_TEXTURE_NUM - 1]->Release();
		m_pTempSurface[TEMP_TEXTURE_NUM - 1] = NULL;
	}
	return bok;
}

bool D3DVideoRender::DrawToWindow(LPBYTE src, int w, int h, int wstride)
{
	assert(m_pd3dDevice);

	if (!m_pSrcVideoTexture || w != m_nWidth || h != m_nHeight)
	{
		SAFE_RELEASE(m_pSrcVideoTexture);
		m_nWidth = w;
		m_nHeight = h;
		CreateTexture(m_nWidth, m_nHeight, &m_pSrcVideoTexture, 0, D3DPOOL_MANAGED);
	}

	if (!CopyToTexture(src, m_pSrcVideoTexture, w, h, wstride))
	{
		MessageBox(0, 0, "CopyToTexture failed", 0);
		return false;
	}

	m_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(123, 65, 255), 1.0f, 0);

	if (SUCCEEDED(m_pd3dDevice->BeginScene()))
	{

		UINT cPasses = 0;
		bool result = false;
		result = m_effect.SetTechnique("vpProcess");
		result = m_effect.Begin(cPasses);

		result = m_effect.SetFloat("width", (float)m_nWidth);
		result = m_effect.SetFloat("height", (float)m_nHeight);
		result = m_effect.SetFloat("step", 1.0f);
		result = m_effect.SetFloat("radius", 10.0f);

		result = m_effect.SetTexture(0, m_pSrcVideoTexture);
		result = m_effect.BeginPass(0);
		
		DrawPass();

		m_effect.EndPass();
		m_effect.End();

		m_pd3dDevice->EndScene();
	}

	m_pd3dDevice->Present(NULL, NULL, NULL, NULL);

	return true; 
}