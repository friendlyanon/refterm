typedef struct
{
    uint32_t CellSize[2];
    uint32_t TermSize[2];
    uint32_t BlinkModulate;
    uint32_t Pad0;
    uint32_t Pad1;
    uint32_t Pad2;
} renderer_const_buffer;

#define RENDERER_CELL_BLINK 0x80000000
typedef struct
{
    uint32_t GlyphIndex;
    uint32_t Foreground;
    uint32_t Background; // NOTE(casey): The top bit of the background flag indicates blinking
} renderer_cell;

typedef struct 
{
    ID3D11Device *Device;
    ID3D11DeviceContext *DeviceContext;
    ID3D11DeviceContext1 *DeviceContext1;
    
    IDXGISwapChain2 *SwapChain;

    // TODO(casey): The original version had a FrameLatencyWaitableObject, but I'm not sure
    // what it was actually needed for?  Maybe it should be reinstated, but I don't think
    // we actually need to wait on D3D - we can just go full speed until it stops us?
    // HANDLE FrameLatencyWaitableObject;
    
    ID3D11ComputeShader *ComputeShader;
    ID3D11PixelShader *PixelShader;
    ID3D11VertexShader *VertexShader;
    
    ID3D11Buffer *ConstantBuffer;
    ID3D11RenderTargetView *RenderTarget;
    ID3D11UnorderedAccessView *RenderView;
    
    ID3D11Buffer *CellBuffer;
    ID3D11ShaderResourceView *CellView;
    
    ID3D11Texture2D *GlyphTexture;
    ID3D11ShaderResourceView *GlyphTextureView;
    
    ID3D11Texture2D *GlyphTransfer;
    ID3D11ShaderResourceView *GlyphTransferView;
    IDXGISurface *GlyphTransferSurface;

    // NOTE(casey): These are for DirectWrite
    struct ID2D1RenderTarget *DWriteRenderTarget;
    struct ID2D1SolidColorBrush *DWriteFillBrush;
    
    uint32_t CurrentWidth;
    uint32_t CurrentHeight;
    
    int UseComputeShader;
} d3d11_renderer;

static d3d11_renderer AcquireD3D11Renderer(HWND Window, int EnableDebugging);

static void ClearD3D11GlyphTexture(d3d11_renderer *Renderer);
static void SetD3D11MaxCellCount(d3d11_renderer *Renderer, uint32_t Count);
static void SetD3D11GlyphCacheDim(d3d11_renderer *Renderer, uint32_t Width, uint32_t Height);
