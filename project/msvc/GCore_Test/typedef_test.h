#pragma once
#include <gtest/gtest.h>
#include "gtype.h"

// �����������͵ĳ����ڵ�ǰƽ̨���Ƿ���Ϲ淶
TEST(TypedefTest, HandleNoneZeroInput)
{
	using namespace gsystem;
	
	// ���涨��λ�����ͣ��䳤���Ƿ���϶���
	ASSERT_EQ(1, sizeof(gchar8)) << "error: gchar8 must be 1 byte(s), but now it's " << sizeof(gchar8) << " byte(s).";
	ASSERT_EQ(2, sizeof(gchar16)) << "error: gchar16 must be 2 byte(s), but now it's " << sizeof(gchar8) << " byte(s).";
	ASSERT_EQ(4, sizeof(gchar32)) << "error: gchar32 must be 4 byte(s), but now it's " << sizeof(gchar8) << " byte(s).";
	
	ASSERT_EQ(1, sizeof(gint8)) << "error: gint8 must be 1 byte(s), but now it's " << sizeof(gint8) << " byte(s).";
	ASSERT_EQ(1, sizeof(guint8)) << "error: guint8 must be 1 byte(s), but now it's " << sizeof(guint8) << " byte(s).";
	ASSERT_EQ(2, sizeof(gint16)) << "error: gint16 must be 2 byte(s), but now it's " << sizeof(gint16) << " byte(s).";
	ASSERT_EQ(2, sizeof(guint16)) << "error: guint16 must be 2 byte(s), but now it's " << sizeof(guint16) << " byte(s).";
	ASSERT_EQ(4, sizeof(gint32)) << "error: gint32 must be 4 byte(s), but now it's " << sizeof(gint32) << " byte(s).";
	ASSERT_EQ(4, sizeof(guint32)) << "error: guint32 must be 4 byte(s), but now it's " << sizeof(guint32) << " byte(s).";
	ASSERT_EQ(8, sizeof(gint64)) << "error: gint64 must be 8 byte(s), but now it's " << sizeof(gint64) << " byte(s).";
	ASSERT_EQ(8, sizeof(guint64)) << "error: guint64 must be 8 byte(s), but now it's " << sizeof(guint64) << " byte(s).";
}