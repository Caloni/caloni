#
# This script converts a csv file with 1 min candles from stock market to
# inserts into a database from several tables with different frequencies.
#
# author Wanderley Caloni <wanderley.caloni@gmail.com>
# date 2020-06
#

function print_insert(table, Timestamp, OpenPrice, HighPrice, LowPrice, ClosePrice, TradeCount, Volume)
{
    print "insert into " table " (Symbol, Timestamp, OpenPrice, HighPrice, LowPrice, ClosePrice, TradeCount, Volume) "\
        "values (" Symbol ", " Timestamp ", " OpenPrice ", " HighPrice " , " LowPrice ", " ClosePrice ", " TradeCount ", " Volume ");"
}


BEGIN { 
    FS = ";";
    Symbol = "abev3";
    candle5["table"] = "5M";
    candle15["table"] = "15M";
    candle30["table"] = "30M";
    candle60["table"] = "1H";
    candle180["table"] = "3H";
    candle24h["table"] = "1D";
    candle7d["table"] = "1W";
    candle30d["table"] = "30D";
}


NR == 1 {
    candle5["open"] = $2
    candle15["open"] = $2
    candle30["open"] = $2
    candle60["open"] = $2
    candle180["open"] = $2
    candle24h["open"] = $2
    candle7d["open"] = $2
    candle30d["open"] = $2
}


{
    print_insert("1M", $1, $2, $3, $4, $5, $6, $7);

    if( $3 > candle5["high"] ) candle5["high"] = $3
    if( candle5["low"] == 0 || $4 < candle5["low"] ) candle5["low"] = $4
    candle5["trades"] += $6
    candle5["vol"] += $7
}


function end_of_candle(end_candle, bigger_candle)
{
    print_insert(end_candle["table"], $1, end_candle["open"], end_candle["high"], end_candle["low"], $5, end_candle["trades"], end_candle["vol"]);

    if( end_candle["high"] > bigger_candle["high"] ) bigger_candle["high"] = end_candle["high"]
    if( bigger_candle["low"] == 0 || end_candle["low"] < bigger_candle["low"] ) bigger_candle["low"] = end_candle["low"]
    bigger_candle["trades"] += end_candle["trades"]
    bigger_candle["vol"] += end_candle["vol"]
}


function begin_candle(candle)
{
    candle["open"] = $2
    candle["high"] = $3
    candle["low"] = $4
    candle["trades"] = $6
    candle["vol"] = $7
}


NR % 5 == 0 { end_of_candle(candle5, candle15); }
NR % 6 == 0 { begin_candle(candle5); }
NR % 15 == 0 { end_of_candle(candle15, candle30); }
NR % 16 == 0 { begin_candle(candle15); }
NR % 30 == 0 { end_of_candle(candle30, candle60); }
NR % 31 == 0 { begin_candle(candle30); }
NR % 60 == 0 { end_of_candle(candle60, candle180); }
NR % 61 == 0 { begin_candle(candle60); }
NR % 180 == 0 { end_of_candle(candle180, candle24h); }
NR % 181 == 0 { begin_candle(candle180); }
NR % 1440 == 0 { end_of_candle(candle24h, candle7d); }
NR % 1441 == 0 { begin_candle(candle24h); }
NR % 10080 == 0 { end_of_candle(candle7d, candle30d); }
NR % 10081 == 0 { begin_candle(candle7d); }
NR % 302400 == 0 { end_of_candle(candle30d, candle60d); }
