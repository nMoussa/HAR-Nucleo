/**
  ******************************************************************************
  * @file    network.c
  * @author  AST Embedded Analytics Research Platform
  * @date    Tue Jul 21 10:03:17 2020
  * @brief   AI Tool Automatic Code Generator for Embedded NN computing
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2018 STMicroelectronics.
  * All rights reserved.
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */


#include "network.h"

#include "ai_platform_interface.h"
#include "ai_math_helpers.h"

#include "core_common.h"
#include "layers.h"

#undef AI_TOOLS_VERSION_MAJOR
#undef AI_TOOLS_VERSION_MINOR
#undef AI_TOOLS_VERSION_MICRO
#define AI_TOOLS_VERSION_MAJOR 5
#define AI_TOOLS_VERSION_MINOR 1
#define AI_TOOLS_VERSION_MICRO 1


#undef AI_TOOLS_API_VERSION_MAJOR
#undef AI_TOOLS_API_VERSION_MINOR
#undef AI_TOOLS_API_VERSION_MICRO
#define AI_TOOLS_API_VERSION_MAJOR 1
#define AI_TOOLS_API_VERSION_MINOR 3
#define AI_TOOLS_API_VERSION_MICRO 0

#undef AI_NET_OBJ_INSTANCE
#define AI_NET_OBJ_INSTANCE g_network
 
#undef AI_NETWORK_MODEL_SIGNATURE
#define AI_NETWORK_MODEL_SIGNATURE     "da105d8eb63546a99d7090eb618073c7"

#ifndef AI_TOOLS_REVISION_ID
#define AI_TOOLS_REVISION_ID     "(rev-5.1.1)"
#endif

#undef AI_TOOLS_DATE_TIME
#define AI_TOOLS_DATE_TIME   "Tue Jul 21 10:03:17 2020"

#undef AI_TOOLS_COMPILE_TIME
#define AI_TOOLS_COMPILE_TIME    __DATE__ " " __TIME__

#undef AI_NETWORK_N_BATCHES
#define AI_NETWORK_N_BATCHES         (1)

/**  Forward network declaration section  *************************************/
AI_STATIC ai_network AI_NET_OBJ_INSTANCE;


/**  Forward network array declarations  **************************************/
AI_STATIC ai_array quantize_2_scratch0_array;   /* Array #0 */
AI_STATIC ai_array quantize_4_bias_array;   /* Array #1 */
AI_STATIC ai_array quantize_4_weights_array;   /* Array #2 */
AI_STATIC ai_array quantize_2_bias_array;   /* Array #3 */
AI_STATIC ai_array quantize_2_weights_array;   /* Array #4 */
AI_STATIC ai_array quantize_1_bias_array;   /* Array #5 */
AI_STATIC ai_array quantize_1_weights_array;   /* Array #6 */
AI_STATIC ai_array input_0_output_array;   /* Array #7 */
AI_STATIC ai_array quantize_1_output_array;   /* Array #8 */
AI_STATIC ai_array quantize_2_output_array;   /* Array #9 */
AI_STATIC ai_array quantize_4_output_array;   /* Array #10 */
AI_STATIC ai_array softmax_1_output_array;   /* Array #11 */


/**  Forward network tensor declarations  *************************************/
AI_STATIC ai_tensor quantize_2_scratch0;   /* Tensor #0 */
AI_STATIC ai_tensor quantize_4_bias;   /* Tensor #1 */
AI_STATIC ai_tensor quantize_4_weights;   /* Tensor #2 */
AI_STATIC ai_tensor quantize_2_bias;   /* Tensor #3 */
AI_STATIC ai_tensor quantize_2_weights;   /* Tensor #4 */
AI_STATIC ai_tensor quantize_1_bias;   /* Tensor #5 */
AI_STATIC ai_tensor quantize_1_weights;   /* Tensor #6 */
AI_STATIC ai_tensor input_0_output;   /* Tensor #7 */
AI_STATIC ai_tensor quantize_1_output;   /* Tensor #8 */
AI_STATIC ai_tensor quantize_2_output;   /* Tensor #9 */
AI_STATIC ai_tensor quantize_4_output;   /* Tensor #10 */
AI_STATIC ai_tensor softmax_1_output;   /* Tensor #11 */


/**  Forward network tensor chain declarations  *******************************/
AI_STATIC_CONST ai_tensor_chain quantize_1_chain;   /* Chain #0 */
AI_STATIC_CONST ai_tensor_chain quantize_2_chain;   /* Chain #1 */
AI_STATIC_CONST ai_tensor_chain quantize_4_chain;   /* Chain #2 */
AI_STATIC_CONST ai_tensor_chain softmax_1_chain;   /* Chain #3 */


/**  Forward network layer declarations  **************************************/
AI_STATIC ai_layer_conv2d quantize_1_layer; /* Layer #0 */
AI_STATIC ai_layer_conv2d_nl_pool quantize_2_layer; /* Layer #1 */
AI_STATIC ai_layer_dense quantize_4_layer; /* Layer #2 */
AI_STATIC ai_layer_nl softmax_1_layer; /* Layer #3 */


/**  Array declarations section  **********************************************/
/* Array#0 */
AI_ARRAY_OBJ_DECLARE(
  quantize_2_scratch0_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 768, AI_STATIC)

/* Array#1 */
AI_ARRAY_OBJ_DECLARE(
  quantize_4_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 5, AI_STATIC)

/* Array#2 */
AI_ARRAY_OBJ_DECLARE(
  quantize_4_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 80, AI_STATIC)

/* Array#3 */
AI_ARRAY_OBJ_DECLARE(
  quantize_2_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 16, AI_STATIC)

/* Array#4 */
AI_ARRAY_OBJ_DECLARE(
  quantize_2_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 1280, AI_STATIC)

/* Array#5 */
AI_ARRAY_OBJ_DECLARE(
  quantize_1_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 16, AI_STATIC)

/* Array#6 */
AI_ARRAY_OBJ_DECLARE(
  quantize_1_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 80, AI_STATIC)

/* Array#7 */
AI_ARRAY_OBJ_DECLARE(
  input_0_output_array, AI_ARRAY_FORMAT_FLOAT|AI_FMT_FLAG_IS_IO,
  NULL, NULL, 72, AI_STATIC)

/* Array#8 */
AI_ARRAY_OBJ_DECLARE(
  quantize_1_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 960, AI_STATIC)

/* Array#9 */
AI_ARRAY_OBJ_DECLARE(
  quantize_2_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 16, AI_STATIC)

/* Array#10 */
AI_ARRAY_OBJ_DECLARE(
  quantize_4_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 5, AI_STATIC)

/* Array#11 */
AI_ARRAY_OBJ_DECLARE(
  softmax_1_output_array, AI_ARRAY_FORMAT_FLOAT|AI_FMT_FLAG_IS_IO,
  NULL, NULL, 5, AI_STATIC)

/**  Tensor declarations section  *********************************************/
/* Tensor #0 */
AI_TENSOR_OBJ_DECLARE(
  quantize_2_scratch0, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 1, 16, 3, 16), AI_STRIDE_INIT(4, 4, 4, 64, 192),
  1, &quantize_2_scratch0_array, NULL)

/* Tensor #1 */
AI_TENSOR_OBJ_DECLARE(
  quantize_4_bias, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 1, 5, 1, 1), AI_STRIDE_INIT(4, 4, 4, 20, 20),
  1, &quantize_4_bias_array, NULL)

/* Tensor #2 */
AI_TENSOR_OBJ_DECLARE(
  quantize_4_weights, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 16, 5, 1, 1), AI_STRIDE_INIT(4, 4, 64, 320, 320),
  1, &quantize_4_weights_array, NULL)

/* Tensor #3 */
AI_TENSOR_OBJ_DECLARE(
  quantize_2_bias, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 1, 16, 1, 1), AI_STRIDE_INIT(4, 4, 4, 64, 64),
  1, &quantize_2_bias_array, NULL)

/* Tensor #4 */
AI_TENSOR_OBJ_DECLARE(
  quantize_2_weights, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 16, 1, 5, 16), AI_STRIDE_INIT(4, 4, 64, 64, 320),
  1, &quantize_2_weights_array, NULL)

/* Tensor #5 */
AI_TENSOR_OBJ_DECLARE(
  quantize_1_bias, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 1, 16, 1, 1), AI_STRIDE_INIT(4, 4, 4, 64, 64),
  1, &quantize_1_bias_array, NULL)

/* Tensor #6 */
AI_TENSOR_OBJ_DECLARE(
  quantize_1_weights, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 1, 1, 5, 16), AI_STRIDE_INIT(4, 4, 4, 4, 20),
  1, &quantize_1_weights_array, NULL)

/* Tensor #7 */
AI_TENSOR_OBJ_DECLARE(
  input_0_output, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 1, 1, 3, 24), AI_STRIDE_INIT(4, 4, 4, 4, 12),
  1, &input_0_output_array, NULL)

/* Tensor #8 */
AI_TENSOR_OBJ_DECLARE(
  quantize_1_output, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 1, 16, 3, 20), AI_STRIDE_INIT(4, 4, 4, 64, 192),
  1, &quantize_1_output_array, NULL)

/* Tensor #9 */
AI_TENSOR_OBJ_DECLARE(
  quantize_2_output, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 1, 16, 1, 1), AI_STRIDE_INIT(4, 4, 4, 64, 64),
  1, &quantize_2_output_array, NULL)

/* Tensor #10 */
AI_TENSOR_OBJ_DECLARE(
  quantize_4_output, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 1, 5, 1, 1), AI_STRIDE_INIT(4, 4, 4, 20, 20),
  1, &quantize_4_output_array, NULL)

/* Tensor #11 */
AI_TENSOR_OBJ_DECLARE(
  softmax_1_output, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 1, 5, 1, 1), AI_STRIDE_INIT(4, 4, 4, 20, 20),
  1, &softmax_1_output_array, NULL)



/**  Layer declarations section  **********************************************/


AI_TENSOR_CHAIN_OBJ_DECLARE(
  quantize_1_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &input_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &quantize_1_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &quantize_1_weights, &quantize_1_bias, NULL),
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  quantize_1_layer, 0,
  CONV2D_TYPE,
  conv2d, forward_conv2d,
  &AI_NET_OBJ_INSTANCE, &quantize_2_layer, AI_STATIC,
  .tensors = &quantize_1_chain, 
  .groups = 1, 
  .nl_func = nl_func_relu_array_f32, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  quantize_2_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &quantize_1_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &quantize_2_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &quantize_2_weights, &quantize_2_bias, NULL),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &quantize_2_scratch0)
)

AI_LAYER_OBJ_DECLARE(
  quantize_2_layer, 1,
  OPTIMIZED_CONV2D_TYPE,
  conv2d_nl_pool, forward_conv2d_nl_pool,
  &AI_NET_OBJ_INSTANCE, &quantize_4_layer, AI_STATIC,
  .tensors = &quantize_2_chain, 
  .groups = 1, 
  .nl_func = nl_func_relu_array_f32, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), 
  .pool_size = AI_SHAPE_2D_INIT(3, 16), 
  .pool_stride = AI_SHAPE_2D_INIT(3, 16), 
  .pool_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), 
  .pool_func = pool_func_mp_array_f32, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  quantize_4_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &quantize_2_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &quantize_4_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &quantize_4_weights, &quantize_4_bias),
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  quantize_4_layer, 3,
  DENSE_TYPE,
  dense, forward_dense,
  &AI_NET_OBJ_INSTANCE, &softmax_1_layer, AI_STATIC,
  .tensors = &quantize_4_chain, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  softmax_1_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &quantize_4_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &softmax_1_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  softmax_1_layer, 4,
  NL_TYPE,
  nl, forward_sm,
  &AI_NET_OBJ_INSTANCE, &softmax_1_layer, AI_STATIC,
  .tensors = &softmax_1_chain, 
)


AI_NETWORK_OBJ_DECLARE(
  AI_NET_OBJ_INSTANCE, AI_STATIC,
  AI_BUFFER_OBJ_INIT(AI_BUFFER_FORMAT_U8,
                     1, 1, 5908, 1,
                     NULL),
  AI_BUFFER_OBJ_INIT(AI_BUFFER_FORMAT_U8,
                     1, 1, 6976, 1,
                     NULL),
  AI_TENSOR_LIST_IO_OBJ_INIT(AI_FLAG_NONE, AI_NETWORK_IN_NUM, &input_0_output),
  AI_TENSOR_LIST_IO_OBJ_INIT(AI_FLAG_NONE, AI_NETWORK_OUT_NUM, &softmax_1_output),
  &quantize_1_layer, 0, NULL)



AI_DECLARE_STATIC
ai_bool network_configure_activations(
  ai_network* net_ctx, const ai_buffer* activation_buffer)
{
  AI_ASSERT(net_ctx &&  activation_buffer && activation_buffer->data)

  ai_ptr activations = AI_PTR(AI_PTR_ALIGN(activation_buffer->data, 4));
  AI_ASSERT(activations)
  AI_UNUSED(net_ctx)

  {
    /* Updating activations (byte) offsets */
    quantize_2_scratch0_array.data = AI_PTR(activations + 3840);
    quantize_2_scratch0_array.data_start = AI_PTR(activations + 3840);
    input_0_output_array.data = AI_PTR(NULL);
    input_0_output_array.data_start = AI_PTR(NULL);
    quantize_1_output_array.data = AI_PTR(activations + 0);
    quantize_1_output_array.data_start = AI_PTR(activations + 0);
    quantize_2_output_array.data = AI_PTR(activations + 6912);
    quantize_2_output_array.data_start = AI_PTR(activations + 6912);
    quantize_4_output_array.data = AI_PTR(activations + 0);
    quantize_4_output_array.data_start = AI_PTR(activations + 0);
    softmax_1_output_array.data = AI_PTR(NULL);
    softmax_1_output_array.data_start = AI_PTR(NULL);
    
  }
  return true;
}



AI_DECLARE_STATIC
ai_bool network_configure_weights(
  ai_network* net_ctx, const ai_buffer* weights_buffer)
{
  AI_ASSERT(net_ctx &&  weights_buffer && weights_buffer->data)

  ai_ptr weights = AI_PTR(weights_buffer->data);
  AI_ASSERT(weights)
  AI_UNUSED(net_ctx)

  {
    /* Updating weights (byte) offsets */
    
    quantize_4_bias_array.format |= AI_FMT_FLAG_CONST;
    quantize_4_bias_array.data = AI_PTR(weights + 5888);
    quantize_4_bias_array.data_start = AI_PTR(weights + 5888);
    quantize_4_weights_array.format |= AI_FMT_FLAG_CONST;
    quantize_4_weights_array.data = AI_PTR(weights + 5568);
    quantize_4_weights_array.data_start = AI_PTR(weights + 5568);
    quantize_2_bias_array.format |= AI_FMT_FLAG_CONST;
    quantize_2_bias_array.data = AI_PTR(weights + 5504);
    quantize_2_bias_array.data_start = AI_PTR(weights + 5504);
    quantize_2_weights_array.format |= AI_FMT_FLAG_CONST;
    quantize_2_weights_array.data = AI_PTR(weights + 384);
    quantize_2_weights_array.data_start = AI_PTR(weights + 384);
    quantize_1_bias_array.format |= AI_FMT_FLAG_CONST;
    quantize_1_bias_array.data = AI_PTR(weights + 320);
    quantize_1_bias_array.data_start = AI_PTR(weights + 320);
    quantize_1_weights_array.format |= AI_FMT_FLAG_CONST;
    quantize_1_weights_array.data = AI_PTR(weights + 0);
    quantize_1_weights_array.data_start = AI_PTR(weights + 0);
  }

  return true;
}


/**  PUBLIC APIs SECTION  *****************************************************/

AI_API_ENTRY
ai_bool ai_network_get_info(
  ai_handle network, ai_network_report* report)
{
  ai_network* net_ctx = AI_NETWORK_ACQUIRE_CTX(network);

  if ( report && net_ctx )
  {
    ai_network_report r = {
      .model_name        = AI_NETWORK_MODEL_NAME,
      .model_signature   = AI_NETWORK_MODEL_SIGNATURE,
      .model_datetime    = AI_TOOLS_DATE_TIME,
      
      .compile_datetime  = AI_TOOLS_COMPILE_TIME,
      
      .runtime_revision  = ai_platform_runtime_get_revision(),
      .runtime_version   = ai_platform_runtime_get_version(),

      .tool_revision     = AI_TOOLS_REVISION_ID,
      .tool_version      = {AI_TOOLS_VERSION_MAJOR, AI_TOOLS_VERSION_MINOR,
                            AI_TOOLS_VERSION_MICRO, 0x0},
      .tool_api_version  = {AI_TOOLS_API_VERSION_MAJOR, AI_TOOLS_API_VERSION_MINOR,
                            AI_TOOLS_API_VERSION_MICRO, 0x0},

      .api_version            = ai_platform_api_get_version(),
      .interface_api_version  = ai_platform_interface_api_get_version(),
      
      .n_macc            = 68923,
      .n_inputs          = 0,
      .inputs            = NULL,
      .n_outputs         = 0,
      .outputs           = NULL,
      .activations       = AI_STRUCT_INIT,
      .params            = AI_STRUCT_INIT,
      .n_nodes           = 0,
      .signature         = 0x0,
    };

    if ( !ai_platform_api_get_network_report(network, &r) ) return false;

    *report = r;
    return true;
  }

  return false;
}

AI_API_ENTRY
ai_error ai_network_get_error(ai_handle network)
{
  return ai_platform_network_get_error(network);
}

AI_API_ENTRY
ai_error ai_network_create(
  ai_handle* network, const ai_buffer* network_config)
{
  return ai_platform_network_create(
    network, network_config, 
    &AI_NET_OBJ_INSTANCE,
    AI_TOOLS_API_VERSION_MAJOR, AI_TOOLS_API_VERSION_MINOR, AI_TOOLS_API_VERSION_MICRO);
}

AI_API_ENTRY
ai_handle ai_network_destroy(ai_handle network)
{
  return ai_platform_network_destroy(network);
}

AI_API_ENTRY
ai_bool ai_network_init(
  ai_handle network, const ai_network_params* params)
{
  ai_network* net_ctx = ai_platform_network_init(network, params);
  if ( !net_ctx ) return false;

  ai_bool ok = true;
  ok &= network_configure_weights(net_ctx, &params->params);
  ok &= network_configure_activations(net_ctx, &params->activations);

  ok &= ai_platform_network_post_init(network);

  return ok;
}


AI_API_ENTRY
ai_i32 ai_network_run(
  ai_handle network, const ai_buffer* input, ai_buffer* output)
{
  return ai_platform_network_process(network, input, output);
}

AI_API_ENTRY
ai_i32 ai_network_forward(ai_handle network, const ai_buffer* input)
{
  return ai_platform_network_process(network, input, NULL);
}


#undef AI_NETWORK_MODEL_SIGNATURE
#undef AI_NET_OBJ_INSTANCE
#undef AI_TOOLS_VERSION_MAJOR
#undef AI_TOOLS_VERSION_MINOR
#undef AI_TOOLS_VERSION_MICRO
#undef AI_TOOLS_API_VERSION_MAJOR
#undef AI_TOOLS_API_VERSION_MINOR
#undef AI_TOOLS_API_VERSION_MICRO
#undef AI_TOOLS_DATE_TIME
#undef AI_TOOLS_COMPILE_TIME

