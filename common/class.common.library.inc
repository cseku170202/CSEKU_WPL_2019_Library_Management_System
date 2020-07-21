<?php


// Library related model
class Library{
    private $_ID;
    private $_name;
    private $_address;
    private $_type;
    private $_librarian;
    private $_returnPolicy;
    private $_maxIssuance;


    public function setID ( $ID ) {
        $this->_ID = $ID;
    }

    public function getID () {
        return $this->_ID;
    }
    public function setName ($Name){
        $this->_name = $Name;
    }
    public function getName(){
        return $this->_name;
    }

    public function setAddress ($Address){
        $this->_address = $Address;
    }
    public function getAddress(){
        return $this->_address;
    }

    public function setType( $Type ) {
        $this->_type = $Type;
    }

    public function getType () {
        return $this->_type;
    }
    public function setLibrarian( $Librarian ) {
        $this->_librarian = $Librarian;
    }

    public function getLibrarian () {
        return $this->_librarian;
    }
     public function setReturnPolicy( $ReturnPolicy ) {
        $this->_returnPolicy= $ReturnPolicy;
    }

    public function getReturnPolicy () {
        return $this->_returnPolicy;
    }
     public function setMaxIssuance( $MaxIssuance ) {
        $this->_maxIssuance = $MaxIssuance;
    }

    public function getMaxIssuance () {
        return $this->_maxIssuance;
    }

}

// Shelf related model
class Shelf{
    private $_ID;
    private $_name;
    private $_capacity;
    private $_library;


    public function setID ( $ID ) {
        $this->_ID = $ID;
    }

    public function getID () {
        return $this->_ID;
    }
    public function setName ($Name){
        $this->_name = $Name;
    }
    public function getName(){
        return $this->_name;
    }

    public function setCapacity ($Capacity){
        $this->_capacity = $Capacity;
    }
    public function getCapacity(){
        return $this->_capacity;
    }

    public function setLibraryId( $Library ) {
        $this->_library = $Library;
    }

    public function getLibraryId() {
        return $this->_library;
    }

}

// Books related model
class Books{
    private $_ID;
    private $_seialNo;
    private $_title;
    private $_author;
    private $_shelfId;
    private $_availableCopies;
    private $_cover;


    public function setID ( $ID ) {
        $this->_ID = $ID;
    }

    public function getID () {
        return $this->_ID;
    }
    public function setSerialNo ($SerialNo){
        $this->_serialNo = $SerialNo;
    }
    public function getSerialNo(){
        return $this->_serialNo;
    }

    public function setTitle ($Title){
        $this->_title = $Title;
    }
    public function getTitle(){
        return $this->_title;
    }

    public function setAuthor( $Author ) {
        $this->_author = $Author;
    }

    public function getAuthor() {
        return $this->_author;
    }
    public function setShelfId( $ShelfId ) {
        $this->_shelfId = $ShelfId;
    }

    public function getShelfId() {
        return $this->_shelfId;
    }
    public function setAvailableCopies( $AvailableCopies ) {
        $this->_availableCopies = $AvailableCopies;
    }

    public function getAvailableCopies() {
        return $this->_availableCopies;
    }
     public function setCover( $Cover ) {
        $this->_cover = $Cover;
    }

    public function getCover() {
        return $this->_cover;
    }

}

/**
*  Issuance Class
*/
class Issuance
{
    private $_ID;
    private $_bookId;
    private $_IssuedTo;
    private $_issueDate;
    private $_issuedDate;
    private $_returnDate;
    private $_status;
    private $_LibraryReturnPolicy;



    public function getID(){
        return $this->_ID;
    }

    public function setID($ID){
        $this->_ID = $ID;
    }

    public function getBookId(){
        return $this->_bookId;
    }

    public function setBookId($bookId){
        $this->_bookId = $bookId;
    }

    public function getIssuedTo(){
        return $this->_IssuedTo;
    }

    public function setIssuedTo($IssuedTo){
        $this->_IssuedTo = $IssuedTo;
    }

    public function getIssueDate(){
        return $this->_issueDate;
    }

    public function setIssueDate($issueDate){
        $this->_issueDate = $issueDate;
    }






   
    public function getIssuedDate(){
        return $this->_issuedDate;
    }

    public function setIssuedDate($issuedDate){
        $this->_issuedDate = $issuedDate;
    }

    





    public function getReturnDate(){
        return $this->_returnDate;
    }

    public function setReturnDate($returnDate){
        $this->_returnDate = $returnDate;
    }

    public function getStatus(){
        return $this->_status;
    }

    public function setStatus($status){
        $this->_status = $status;
    }


    public function getLibraryReturnPolicy(){
        return $this->_LibraryReturnPolicy;
    }

    public function setLibraryReturnPolicy($LibraryReturnPolicy){
        $this->_LibraryReturnPolicy= $LibraryReturnPolicy;
    }

}
/**
* Browse and issue book
*/
class Browse_Library
{
    private $ID;
    private $_userId;
    private $_bookId;

    public function getID(){
        return $this->_ID;
    }

    public function setID($ID){
        $this->_ID = $ID;
    }

    public function getBookId(){
        return $this->_bookId;
    }

    public function setBookId($bookId){
        $this->_bookId = $bookId;
    }

    public function getUserId(){
        return $this->_userId;
    }

    public function setUserId($UserId){
        $this->_userId = $UserId;
    }
}
/**
* Checkout class
*/
class Checkout
{
    private $ID;
    private $_userId;
    private $_bookId;
    private $_LibraryName;
    private $_LibraryReturnPolicy;
    private $_LibraryMaxIssuance;

    public function getID(){
        return $this->_ID;
    }

    public function setID($ID){
        $this->_ID = $ID;
    }

    public function getBookId(){
        return $this->_bookId;
    }

    public function setBookId($bookId){
        $this->_bookId = $bookId;
    }

    public function getUserId(){
        return $this->_userId;
    }

    public function setUserId($UserId){
        $this->_userId = $UserId;
    }
    public function getLibraryName(){
        return $this->_LibraryName;
    }

    public function setLibraryName($LibraryName){
        $this->_LibraryName= $LibraryName;
    }

    public function getLibraryReturnPolicy(){
        return $this->_LibraryReturnPolicy;
    }

    public function setLibraryReturnPolicy($LibraryReturnPolicy){
        $this->_LibraryReturnPolicy= $LibraryReturnPolicy;
    }

    public function getLibraryMaxIssuance(){
        return $this->_LibraryMaxIssuance;
    }

    public function setLibraryMaxIssuance($LibraryMaxIssuance){
        $this->_LibraryMaxIssuance= $LibraryMaxIssuance;
    }
}




class Notify
{
    private $_ID;
    private $_userId;
    private $_message;
    private $_toUser;
    private $_fromModule;
    private $_isSeen;
    private $_isSent;

    public function getID(){
        return $this->_ID;
    }

    public function setID($ID){
        $this->_ID = $ID;
    }

    public function getUserId(){
        return $this->_userId;
    }

    public function setUserId($UserId){
        $this->_userId = $UserId;
    }

    public function getMessage(){
        return $this->_message;
    }

    public function setMessage($Message){
        $this->_message = $Message;
    }

    public function getToUser(){
        return $this->_toUser;
    }

    public function setToUser($ToUser){
        $this->_toUser = $ToUser;
    }

    public function getFromModule(){
        return $this->_fromModule;
    }

    public function setFromModule($FromModule){
        $this->_fromModule = $FromModule;
    }

    public function getIsSeen(){
        return $this->_isSeen;
    }

    public function setIsSeen($IsSeen){
        $this->_isSeen = $IsSeen;
    }

    public function getIsSent(){
        return $this->_isSent;
    }

    public function setIsSent($IsSent){
        $this->_isSent = $IsSent;
    }

}



class Fine
{
    private $ID;
    private $_userFine;
    private $_library;

    public function getID(){
        return $this->_ID;
    }

    public function setID($ID){
        $this->_ID = $ID;
    }

    public function getUserFine(){
        return $this->_userFine;
    }

    public function setUserFine($userFine){
        $this->_userFine = $userFine;
    }

    public function setLibraryId($Library) {
        $this->_library = $Library;
    }

    public function getLibraryId() {
        return $this->_library;
    }

}








?>