/*
 * Copyright 2021 Google LLC
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package com.jnibind.test;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertTrue;

import java.util.Arrays;
import org.junit.AfterClass;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.junit.runners.JUnit4;

/** Exercises array functionality arcross rJNI. */
@RunWith(JUnit4.class)
public class ArrayTest {
  static {
    System.loadLibrary("array_test_jni");
  }

  @AfterClass
  public static void doShutDown() {
    jniTearDown();
  }

  static native void jniTearDown();

  /** 1D Tests JNI declarations. * */
  native void nativeBooleanTests(ArrayTest arrayTest, boolean[] intArray);

  native void nativeByteTests(ArrayTest arrayTest, byte[] byteArray);

  native void nativeCharTests(ArrayTest arrayTest, char[] charArray);

  native void nativeShortTests(ArrayTest arrayTest, short[] shortArray);

  native void nativeIntTests(ArrayTest arrayTest, int[] intArray);

  native void nativeLongTests(ArrayTest arrayTest, long[] longArray);

  native void nativeFloatTests(ArrayTest arrayTest, float[] floatArray);

  native void nativeDoubleTests(ArrayTest arrayTest, double[] doubleArray);

  native void nativeObjectTests(ArrayTest arrayTest, ObjectTestHelper[] objectArray);

  /** 2D Tests JNI declarations. * */
  native void nativeBooleanTests2D(ArrayTest arrayTest, boolean[][] intArray);

  native void nativeByteTests2D(ArrayTest arrayTest, byte[][] byteArray);

  native void nativeCharTests2D(ArrayTest arrayTest, char[][] charArray);

  native void nativeShortTests2D(ArrayTest arrayTest, short[][] shortArray);

  native void nativeIntTests2D(ArrayTest arrayTest, int[][] intArray);

  native void nativeLongTests2D(ArrayTest arrayTest, long[][] longArray);

  native void nativeFloatTests2D(ArrayTest arrayTest, float[][] floatArray);

  native void nativeDoubleTests2D(ArrayTest arrayTest, double[][] doubleArray);

  native void nativeObjectTests2D(ArrayTest arrayTest, ObjectTestHelper[][] objectArray);

  /** 1D Tests RJNI declarations. * */
  void rJniBooleanArray(boolean testForTrue, boolean[] arr) {
    for (int i = 0; i < arr.length; i++) {
      if (testForTrue) {
        assertTrue(arr[i]);
      } else {
        assertFalse(arr[i]);
      }
    }
  }

  void rJniByteArray(byte baseOffset, byte[] arr) {
    for (int i = 0; i < arr.length; i++) {
      assertEquals(i + baseOffset, arr[i]);
    }
  }

  void rJniCharArray(char baseOffset, char[] arr) {
    for (int i = 0; i < arr.length; i++) {
      assertEquals(i + baseOffset, arr[i]);
    }
  }

  void rJniShortArray(short baseOffset, short[] arr) {
    for (int i = 0; i < arr.length; i++) {
      assertEquals(i + baseOffset, arr[i]);
    }
  }

  void rJniIntArray(int baseOffset, int[] arr) {
    for (int i = 0; i < arr.length; i++) {
      assertEquals(i + baseOffset, arr[i]);
    }
  }

  void rJniLongArray(long baseOffset, long[] arr) {
    for (int i = 0; i < arr.length; i++) {
      assertEquals(i + baseOffset, arr[i]);
    }
  }

  void rJniFloatArray(float baseOffset, float[] arr) {
    for (int i = 0; i < arr.length; i++) {
      assertEquals(i + baseOffset, arr[i], 1.f);
    }
  }

  void rJniDoubleArray(double baseOffset, double[] arr) {
    for (int i = 0; i < arr.length; i++) {
      assertEquals((double) i + baseOffset, arr[i], 0);
    }
  }

  void rJniObjectArray(int objectMemberOffset, ObjectTestHelper[] arr) {
    for (int i = 0; i < arr.length; i++) {
      int idxPlusOffset = i + objectMemberOffset;
      ObjectTestHelper dummyThatMatchesIdx =
          new ObjectTestHelper(idxPlusOffset, idxPlusOffset, idxPlusOffset);
      assertTrue(dummyThatMatchesIdx.isEqualTo(arr[i]));
    }
  }

  /** 2D Tests RJNI declarations. * */
  void rJniBooleanArray2D(boolean testForTrue, boolean[][] arr) {
    // All even are true (unless testForTrue when they're flipped).
    for (int i = 0; i < arr.length; i++) {
      for (int j = 0; j < arr[i].length; j++) {
        boolean hotBit = (i + j) % 2 == 0;
        boolean expectTrue = testForTrue ? hotBit : !hotBit;

        if (expectTrue) {
          assertTrue(arr[i][j]);
        } else {
          assertFalse(arr[i][j]);
        }
      }
    }
  }

  /*
  void rJniByteArray2D(byte baseOffset, byte[][] arr) {
    for (int i = 0; i < arr.length; i++) {
      for (int j = 0; j < arr[i].length; j++) {
      assertEquals(i + baseOffset, arr[i]);
      }
    }
  }

  void rJniCharArray2D(char baseOffset, char[][] arr) {
    for (int i = 0; i < arr.length; i++) {
      for (int j = 0; j < arr[i].length; j++) {
      assertEquals(i + baseOffset, arr[i]);
    }
  }

  void rJniShortArray2D(short baseOffset, short[][] arr) {
    for (int i = 0; i < arr.length; i++) {
      assertEquals(i + baseOffset, arr[i]);
    }
  }

  void rJniIntArray2D(int baseOffset, int[][] arr) {
    for (int i = 0; i < arr.length; i++) {
      assertEquals(i + baseOffset, arr[i]);
    }
  }

  void rJniLongArray2D(long baseOffset, long[][] arr) {
    for (int i = 0; i < arr.length; i++) {
      assertEquals(i + baseOffset, arr[i]);
    }
  }

  void rJniFloatArray2D(float baseOffset, float[][] arr) {
    for (int i = 0; i < arr.length; i++) {
      assertEquals(i + baseOffset, arr[i], 1.f);
    }
  }

  void rJniDoubleArray2D(double baseOffset, double[][] arr) {
    for (int i = 0; i < arr.length; i++) {
      assertEquals((double) i + baseOffset, arr[i], 0);
    }
  }
  */

  void rJniObjectArray2D(int objectMemberOffset, ObjectTestHelper[][] arr) {
    /*
       // jif
    for (int i = 0; i < arr.length; i++) {
      int idxPlusOffset = i + objectMemberOffset;
      ObjectTestHelper dummyThatMatchesIdx =
          new ObjectTestHelper(idxPlusOffset, idxPlusOffset, idxPlusOffset);
      assertTrue(dummyThatMatchesIdx.isEqualTo(arr[i]));
    }
    */
  }

  /** 1D Tests. * */
  @Test
  public void booleanTests() {
    boolean[] arr = {false, false, false};
    nativeBooleanTests(this, arr);
  }

  @Test
  public void byteTests() {
    byte[] arr = {0, 1, 2, 3, 4, 5};
    nativeByteTests(this, arr);
  }

  @Test
  public void charTests() {
    char[] arr = {0, 1, 2, 3, 4, 5};
    nativeCharTests(this, arr);
  }

  @Test
  public void shortTests() {
    short[] arr = {0, 1, 2, 3, 4, 5};
    nativeShortTests(this, arr);
  }

  @Test
  public void intTests() {
    int[] arr = {0, 1, 2, 3, 4, 5};
    nativeIntTests(this, arr);
  }

  @Test
  public void longTests() {
    long[] arr = {0, 1, 2, 3, 4, 5};
    nativeLongTests(this, arr);
  }

  @Test
  public void floatTests() {
    float[] arr = {0, 1, 2, 3, 4, 5};
    nativeFloatTests(this, arr);
  }

  @Test
  public void doubleTests() {
    double[] arr = {0, 1, 2, 3, 4, 5};
    nativeDoubleTests(this, arr);
  }

  @Test
  public void objectTests() {
    ObjectTestHelper[] objectTestHelper = {
      new ObjectTestHelper(0, 0, 0), new ObjectTestHelper(1, 1, 1), new ObjectTestHelper(2, 2, 2)
    };

    nativeObjectTests(this, objectTestHelper);
  }

  /** 2D Tests. * */
  @Test
  public void booleanTests2D() {
    boolean[][] arr = {
      {true, false, true},
      {false, true, false},
      {true, false, true}
    };

    System.out.println(Arrays.toString(arr[0]));
    nativeBooleanTests2D(this, arr);
    System.out.println(Arrays.toString(arr[0]));
    // System.out.println(Arrays.toString(arr));
  }

  /*
  @Test
  public void byteTests2D() {
    byte[][] arr = {
      {0, 1, 2, 3, 4, 5},
      {6, 7, 8, 9, 10, 11},
      {12, 13, 14, 15, 16, 17}};
    nativeByteTests2D(this, arr);
  }

  @Test
  public void charTests2D() {
    char[] arr = {0, 1, 2, 3, 4, 5};
    nativeCharTests2D(this, arr);
  }

  @Test
  public void shortTests2D() {
    short[] arr = {0, 1, 2, 3, 4, 5};
    nativeShortTests2D(this, arr);
  }

  @Test
  public void intTests2D() {
    int[] arr = {0, 1, 2, 3, 4, 5};
    nativeIntTests2D(this, arr);
  }

  @Test
  public void longTests2D() {
    long[] arr = {0, 1, 2, 3, 4, 5};
    nativeLongTests2D(this, arr);
  }

  @Test
  public void floatTests2D() {
    float[] arr = {0, 1, 2, 3, 4, 5};
    nativeFloatTests2D(this, arr);
  }

  @Test
  public void doubleTests2D() {
    double[] arr = {0, 1, 2, 3, 4, 5};
    nativeDoubleTests2D(this, arr);
  }

  @Test
  public void objectTests2D() {
    ObjectTestHelper[] objectTestHelper = {
      new ObjectTestHelper(0, 0, 0), new ObjectTestHelper(1, 1, 1), new ObjectTestHelper(2, 2, 2)
    };

    nativeObjectTests2D(this, objectTestHelper);
  }
  */
}
