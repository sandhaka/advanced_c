#include <stdio.h>

// f1 and f2 should not point to the same memory
void float_copy(float * restrict f1, const float * restrict f2, int length)
{
    // That's why the loop operation is completely indipendet,
    // the compiler can do some optimizations
    for (int i = 0; i < length; i++)
        f1[i] = f2[i];
}

int main(void) {
    
    // const
    const float f = 0;                  // Constant float value
    const float *f_ptr;                 // Pointer to a constant float value
    float * const f_c_ptr;              // Constant pointer to a float value
    const float * const c_f_c_ptr = &f; // Constant opinter to a constant float value

    f_ptr = &f;             // Legal
    // f_c_ptr = &f;        // Illegal, constant pointer

    int k = 4;
    int *const p = &k;   
    int r = 3;
    // p = &r;              // Illegal, constant pointer

    // restrict
    float f1[100] = { [0] = 2.5, [10] = 1.0, [99] = 200.0 };
    float f2[100] = { [0] = 201, [10] = 134.0, [99] = 1.0 };

    float_copy(f1, f2, 100);

    for (int i = 0; i < 100; i++)
    {
        if (f1[i] == 0 && f2[i] == 0)
            continue;

        printf("f1[%d]: %f\n", i, f1[i]);
        printf("f2[%d]: %f\n", i, f2[i]);
    }
}
