using UnityEngine;
using System.Collections;

public class spawnFood : MonoBehaviour {

    public GameObject foodPrefab;
    int count;

    public Transform borderTop;
    public Transform borderBottom;
    public Transform borderLeft;
    public Transform borderRight;

    void Start() {
        InvokeRepeating("Spawn", 2, 4);

    }

    void Update() {
        
    }

    void Spawn() {
        // x position between left & right border
        int x = (int)Random.Range(borderLeft.position.x, borderRight.position.x);

        // y position between top & bottom border
        int y = (int)Random.Range(borderBottom.position.y, borderTop.position.y);

        // Instantiate the food at (x, y)
        Instantiate(foodPrefab, new Vector2(x, y), Quaternion.identity);
    }
}
