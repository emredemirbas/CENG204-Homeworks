// Name: Emre Demirbaş
// ID: 21050111069

#include <stdio.h>
#include <stdlib.h>

// Q1: https://leetcode.com/problems/find-pivot-index/

int Q1_for_solution(int *nums, int numsSize) {
    // find totalSum of the nums.
    int totalSum = 0;
    for (int i = 0; i < numsSize; i++) {
        totalSum += nums[i];
    }

    // Edge case: totalSum may be equal to the first element of the array.
    // For example, nums = [2,1,-1] => pivotIndex must be 0.
    if (totalSum == nums[0])
        return 0;

    int leftSum = 0;
    int rightSum = totalSum;
    for (int i = 1; i < numsSize; i++) {
        // in this loop, nums[i] is potentially pivot.
        leftSum += nums[i - 1]; // update leftSum
        rightSum -= (nums[i - 1] + nums[i]); // update rightSum
        // if each sum is equal, 'i' is the pivotIndex.
        if (leftSum == rightSum) {
            return i;
        }
        rightSum += nums[i]; // in above, I also subtracted our potential pivot. If nums[i] is not pivot, add it back to rightSum.
    }

    return -1; // return -1 if no pivot is found.
}

int Q1_for_to_goto_solution(int *nums, int numsSize) {
    int totalSum = 0;
    int i = 0;

    goto testFirstLoop;

    firstLoop:
    totalSum += nums[i++];

    testFirstLoop:
    if (i < numsSize)
        goto firstLoop;

    if (totalSum == nums[0])
        return 0;

    ////////////////////////////////////////////////////

    int leftSum = 0;
    int rightSum = totalSum;
    i = 1;

    goto testSecondLoop;

    secondLoop:
    leftSum += nums[i - 1];
    rightSum -= (nums[i - 1] + nums[i]);
    if (leftSum == rightSum) {
        return i;
    }
    rightSum += nums[i++];

    testSecondLoop:
    if (i < numsSize)
        goto secondLoop;

    return -1;
}



// Q2: https://leetcode.com/problems/two-sum-ii-input-array-is-sorted/description/

int *Q2_while_solution(int *numbers, int numbersSize, int target, int *returnSize) {
    // set returnSize to 2 (I think returnSize is not necessary
    // for this problem since we always should return 2 integers, but I obeyed the leetcode's rules.)
    *returnSize = 2;
    int *result = (int *) malloc(*returnSize * sizeof(int));
    result[0] = result[1] = -1; // if target is not found, [-1,-1] must be returned.

    // You can think leftIndex and rightIndex as two pointers. (note that they should be different.)
    int leftIndex = 0;
    int rightIndex = numbersSize - 1;

    while (leftIndex < rightIndex) {
        // It is known that input array is always sorted in non-decreasing order.
        int currentSum = numbers[leftIndex] + numbers[rightIndex];

        // if target is found, assign these two indexes to the result array.
        if (currentSum == target) {
            result[0] = leftIndex + 1;
            result[1] = rightIndex + 1;
            return result;
        }
            // if the currentSum is greater than the target, move rightIndex to <-.
        else if (currentSum > target) {
            rightIndex--;
        }
            // if the currentSum is lower than the target, move leftIndex to ->.
        else {
            leftIndex++;
        }
    }

    return result;
}

int *Q2_while_to_jm_goto_solution(int *numbers, int numbersSize, int target, int *returnSize) {
    *returnSize = 2;
    int *result = (int *) malloc(*returnSize * sizeof(int));
    result[0] = result[1] = -1;

    int leftIndex = 0;
    int rightIndex = numbersSize - 1;
    int currentSum;

    goto test;

    loop:
    currentSum = numbers[leftIndex] + numbers[rightIndex];
    if (currentSum == target) {
        result[0] = leftIndex + 1;
        result[1] = rightIndex + 1;
        goto end;
    } else if (currentSum > target) {
        rightIndex--;
    } else {
        leftIndex++;
    }

    test:
    if (leftIndex < rightIndex)
        goto loop;

    end:
    return result;
}

int *Q2_while_to_dw_goto_solution(int *numbers, int numbersSize, int target, int *returnSize) {
    *returnSize = 2;
    int *result = (int *) malloc(*returnSize * sizeof(int));
    result[0] = result[1] = -1;

    int leftIndex = 0;
    int rightIndex = numbersSize - 1;
    int currentSum;

    if (leftIndex >= rightIndex)
        goto end;

    loop:
    currentSum = numbers[leftIndex] + numbers[rightIndex];
    if (currentSum == target) {
        result[0] = leftIndex + 1;
        result[1] = rightIndex + 1;
        goto end;
    } else if (currentSum > target) {
        rightIndex--;
    } else {
        leftIndex++;
    }
    if (leftIndex < rightIndex)
        goto loop;

    end:
    return result;
}

void print_q2_answer(int *result) {
    printf("[%d, %d]\n", result[0], result[1]);
}

int main() {

    int nums1[] = {1, 7, 3, 6, 5, 6};
    int nums2[] = {1, 2, 3};
    int nums3[] = {2, 1, -1};
    int nums4[] = {2, 3, -1, 8, 4};
    int nums5[] = {1, -1, 4};
    int nums6[] = {2, 5};
    printf("Testing Q1:\n");
    printf("\nCase 1: nums = [1,7,3,6,5,6]");
    printf("\nOutput: 3");
    printf("\nResult for Q1_for_solution: %d\n", Q1_for_solution(nums1, sizeof(nums1) / sizeof(int)));
    printf("Result for Q1_for_to_goto_solution: %d\n", Q1_for_to_goto_solution(nums1, sizeof(nums1) / sizeof(int)));

    printf("\nCase 2: nums = [1, 2, 3]");
    printf("\nOutput: -1");
    printf("\nResult for Q1_for_solution: %d\n", Q1_for_solution(nums2, sizeof(nums2) / sizeof(int)));
    printf("Result for Q1_for_to_goto_solution: %d\n", Q1_for_to_goto_solution(nums2, sizeof(nums2) / sizeof(int)));

    printf("\nCase 3: nums = [2,1,-1]");
    printf("\nOutput: 0");
    printf("\nResult for Q1_for_solution: %d\n", Q1_for_solution(nums3, sizeof(nums3) / sizeof(int)));
    printf("Result for Q1_for_to_goto_solution: %d\n", Q1_for_to_goto_solution(nums3, sizeof(nums3) / sizeof(int)));

    printf("\nCase 4: nums = [2, 3, -1, 8, 4]");
    printf("\nOutput: 3");
    printf("\nResult for Q1_for_solution: %d\n", Q1_for_solution(nums4, sizeof(nums4) / sizeof(int)));
    printf("Result for Q1_for_to_goto_solution: %d\n", Q1_for_to_goto_solution(nums4, sizeof(nums4) / sizeof(int)));

    printf("\nCase 5: nums = [1,-1,4]");
    printf("\nOutput: 2");
    printf("\nResult for Q1_for_solution: %d\n", Q1_for_solution(nums5, sizeof(nums5) / sizeof(int)));
    printf("Result for Q1_for_to_goto_solution: %d\n", Q1_for_to_goto_solution(nums5, sizeof(nums5) / sizeof(int)));

    printf("\nCase 6: nums = [2,5]");
    printf("\nOutput: -1");
    printf("\nResult for Q1_for_solution: %d\n", Q1_for_solution(nums6, sizeof(nums6) / sizeof(int)));
    printf("Result for Q1_for_to_goto_solution: %d\n", Q1_for_to_goto_solution(nums6, sizeof(nums6) / sizeof(int)));

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Q2
    int numbers1[] = {2, 7, 11, 15};
    int numbers2[] = {2, 3, 4};
    int numbers3[] = {-1, 0};

    int target1 = 9;
    int target2 = 6;
    int target3 = -1;

    int k = 0;
    int *p = &k;

    printf("\n-----------------------------------------------------------------------\n\n");
    printf("Testing Q2:\n");

    printf("\nCase 1:\nnumbers = [2,7,11,15], target = 9\n");
    printf("Output: [1,2]");
    printf("\nResult for Q2_while_solution: ");
    print_q2_answer(Q2_while_solution(numbers1, sizeof(numbers1) / sizeof(int), target1, p));
    printf("Result for Q2_while_to_jm_goto_solution: ");
    print_q2_answer(Q2_while_to_jm_goto_solution(numbers1, sizeof(numbers1) / sizeof(int), target1, p));
    printf("Result for Q2_while_to_dw_goto_solution: ");
    print_q2_answer(Q2_while_to_dw_goto_solution(numbers1, sizeof(numbers1) / sizeof(int), target1, p));

    printf("\nCase 2:\nnumbers = [2,3,4], target = 6\n");
    printf("Output: [1,3]");
    printf("\nResult for Q2_while_solution: ");
    print_q2_answer(Q2_while_solution(numbers2, sizeof(numbers2) / sizeof(int), target2, p));
    printf("Result for Q2_while_to_jm_goto_solution: ");
    print_q2_answer(Q2_while_to_jm_goto_solution(numbers2, sizeof(numbers2) / sizeof(int), target2, p));
    printf("Result for Q2_while_to_dw_goto_solution: ");
    print_q2_answer(Q2_while_to_dw_goto_solution(numbers2, sizeof(numbers2) / sizeof(int), target2, p));

    printf("\nCase 3:\nnumbers = [-1,0], target = -1\n");
    printf("Output: [1,2]");
    printf("\nResult for Q2_while_solution: ");
    print_q2_answer(Q2_while_solution(numbers3, sizeof(numbers3) / sizeof(int), target3, p));
    printf("Result for Q2_while_to_jm_goto_solution: ");
    print_q2_answer(Q2_while_to_jm_goto_solution(numbers3, sizeof(numbers3) / sizeof(int), target3, p));
    printf("Result for Q2_while_to_dw_goto_solution: ");
    print_q2_answer(Q2_while_to_dw_goto_solution(numbers3, sizeof(numbers3) / sizeof(int), target3, p));


    return 0;
}