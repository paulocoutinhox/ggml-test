#include "whisper.h"
#include "ggml.h"

int main()
{
    // test ggml symbols
    {
        struct ggml_init_params params = {
            .mem_size = 16 * 1024 * 1024,
            .mem_buffer = NULL,
        };

        struct ggml_context *ctx = ggml_init(params);
        ggml_free(ctx);
    }

    // test whisper symbols
    {
        struct whisper_context *ctx = whisper_init_from_file("ggml-base.en.bin");
        whisper_free(ctx);
    }
}
