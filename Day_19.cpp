class Solution {
public:
    // Step 1: Inorder traversal to get sorted values
    void inorder(TreeNode* root, vector<int>& arr) {
        if (!root) return;
        inorder(root->left, arr);
        arr.push_back(root->val);
        inorder(root->right, arr);
    }

    // Step 2: Build balanced BST from sorted array
    TreeNode* buildBST(vector<int>& arr, int start, int end) {
        if (start > end) return nullptr;

        int mid = start + (end - start) / 2;
        TreeNode* root = new TreeNode(arr[mid]);

        root->left = buildBST(arr, start, mid - 1);
        root->right = buildBST(arr, mid + 1, end);

        return root;
    }

    TreeNode* balanceBST(TreeNode* root) {
        vector<int> arr;
        inorder(root, arr);                 // get sorted values
        return buildBST(arr, 0, arr.size() - 1);  // build balanced BST
    }
};
