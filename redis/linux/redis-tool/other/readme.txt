1 debug.bz2 ����Ǵ���debug��Ϣ��redisԴ�룬����redis3.0 unstable
2 test.bz2 ����redis���ݺ�client�Ĳ��԰�
3 redis-3.0.2.debug.migrate ����debug���޸ĺ�Ĵ���password��֤��redisԴ���
   2015/06/18 �����޸���hiredis/asyn.c:__redisAsyncCommand:
    /* Always schedule a write when the write buffer is non-empty */
    // _EL_ADD_WRITE(ac);
	redisAsyncHandleWrite(ac);
	redisAsyncCommand������д�뻺�棬Ȼ��ע��һ��д�ĺ������¼��⣬�ȴ��¼��ⷢ��fd��д֮�������������������д���Ұ�������write�¼�ȥ���ˣ�ֱ�ӷ��͡�
