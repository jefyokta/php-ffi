const char* TF_Version(void);

typedef struct TF_Graph TF_Graph;
typedef struct TF_Status TF_Status;
typedef struct TF_SessionOptions TF_SessionOptions;
typedef struct TF_Session TF_Session;
typedef struct TF_Buffer TF_Buffer;
typedef struct TF_Tensor TF_Tensor;

TF_Graph* TF_NewGraph(void);
void TF_DeleteGraph(TF_Graph*);

TF_Status* TF_NewStatus(void);
void TF_DeleteStatus(TF_Status*);

TF_SessionOptions* TF_NewSessionOptions(void);
void TF_DeleteSessionOptions(TF_SessionOptions*);

TF_Session* TF_NewSession(TF_Graph*, const TF_SessionOptions*, TF_Status*);
void TF_CloseSession(TF_Session*, TF_Status*);
void TF_DeleteSession(TF_Session*, TF_Status*);

TF_Buffer* TF_NewBuffer(void);
TF_Buffer* TF_NewBufferFromString(const void* proto, size_t proto_len);
void TF_DeleteBuffer(TF_Buffer*);

void TF_SessionRun(
    TF_Session* session,
    const void* run_options,
    const char* const* input_names,
    TF_Tensor* const* inputs,
    int ninputs,
    const char* const* output_names,
    TF_Tensor** outputs,
    int noutputs,
    const char* const* target_oper_names,
    int ntargets,
    TF_Status* status);

TF_Tensor* TF_AllocateTensor(int data_type, const int64_t* dims, int num_dims, size_t len);
void TF_DeleteTensor(TF_Tensor*);
void* TF_TensorData(const TF_Tensor*);
size_t TF_TensorByteSize(const TF_Tensor*);

int TF_GraphImportGraphDef(TF_Graph*, const TF_Buffer*, const void* options, TF_Status*);

int TF_GetCode(const TF_Status*);
const char* TF_Message(const TF_Status*);
TF_Session* TF_LoadSessionFromSavedModel(
    const TF_SessionOptions* session_options,
    const void* run_options,
    const char* export_dir,
    const char* const* tags,
    int tags_len,
    TF_Graph* graph,
    void* meta_graph_def,
    TF_Status* status);
